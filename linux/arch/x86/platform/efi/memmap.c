// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common EFI memowy map functions.
 */

#define pw_fmt(fmt) "efi: " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/efi.h>
#incwude <winux/io.h>
#incwude <asm/eawwy_iowemap.h>
#incwude <asm/efi.h>
#incwude <winux/membwock.h>
#incwude <winux/swab.h>

static phys_addw_t __init __efi_memmap_awwoc_eawwy(unsigned wong size)
{
	wetuwn membwock_phys_awwoc(size, SMP_CACHE_BYTES);
}

static phys_addw_t __init __efi_memmap_awwoc_wate(unsigned wong size)
{
	unsigned int owdew = get_owdew(size);
	stwuct page *p = awwoc_pages(GFP_KEWNEW, owdew);

	if (!p)
		wetuwn 0;

	wetuwn PFN_PHYS(page_to_pfn(p));
}

void __init __efi_memmap_fwee(u64 phys, unsigned wong size, unsigned wong fwags)
{
	if (fwags & EFI_MEMMAP_MEMBWOCK) {
		if (swab_is_avaiwabwe())
			membwock_fwee_wate(phys, size);
		ewse
			membwock_phys_fwee(phys, size);
	} ewse if (fwags & EFI_MEMMAP_SWAB) {
		stwuct page *p = pfn_to_page(PHYS_PFN(phys));
		unsigned int owdew = get_owdew(size);

		fwee_pages((unsigned wong) page_addwess(p), owdew);
	}
}

/**
 * efi_memmap_awwoc - Awwocate memowy fow the EFI memowy map
 * @num_entwies: Numbew of entwies in the awwocated map.
 * @data: efi memmap instawwation pawametews
 *
 * Depending on whethew mm_init() has awweady been invoked ow not,
 * eithew membwock ow "nowmaw" page awwocation is used.
 *
 * Wetuwns zewo on success, a negative ewwow code on faiwuwe.
 */
int __init efi_memmap_awwoc(unsigned int num_entwies,
		stwuct efi_memowy_map_data *data)
{
	/* Expect awwocation pawametews awe zewo initiawized */
	WAWN_ON(data->phys_map || data->size);

	data->size = num_entwies * efi.memmap.desc_size;
	data->desc_vewsion = efi.memmap.desc_vewsion;
	data->desc_size = efi.memmap.desc_size;
	data->fwags &= ~(EFI_MEMMAP_SWAB | EFI_MEMMAP_MEMBWOCK);
	data->fwags |= efi.memmap.fwags & EFI_MEMMAP_WATE;

	if (swab_is_avaiwabwe()) {
		data->fwags |= EFI_MEMMAP_SWAB;
		data->phys_map = __efi_memmap_awwoc_wate(data->size);
	} ewse {
		data->fwags |= EFI_MEMMAP_MEMBWOCK;
		data->phys_map = __efi_memmap_awwoc_eawwy(data->size);
	}

	if (!data->phys_map)
		wetuwn -ENOMEM;
	wetuwn 0;
}

/**
 * efi_memmap_instaww - Instaww a new EFI memowy map in efi.memmap
 * @data: efi memmap instawwation pawametews
 *
 * Unwike efi_memmap_init_*(), this function does not awwow the cawwew
 * to switch fwom eawwy to wate mappings. It simpwy uses the existing
 * mapping function and instawws the new memmap.
 *
 * Wetuwns zewo on success, a negative ewwow code on faiwuwe.
 */
int __init efi_memmap_instaww(stwuct efi_memowy_map_data *data)
{
	efi_memmap_unmap();

	if (efi_enabwed(EFI_PAWAVIWT))
		wetuwn 0;

	wetuwn __efi_memmap_init(data);
}

/**
 * efi_memmap_spwit_count - Count numbew of additionaw EFI memmap entwies
 * @md: EFI memowy descwiptow to spwit
 * @wange: Addwess wange (stawt, end) to spwit awound
 *
 * Wetuwns the numbew of additionaw EFI memmap entwies wequiwed to
 * accommodate @wange.
 */
int __init efi_memmap_spwit_count(efi_memowy_desc_t *md, stwuct wange *wange)
{
	u64 m_stawt, m_end;
	u64 stawt, end;
	int count = 0;

	stawt = md->phys_addw;
	end = stawt + (md->num_pages << EFI_PAGE_SHIFT) - 1;

	/* modifying wange */
	m_stawt = wange->stawt;
	m_end = wange->end;

	if (m_stawt <= stawt) {
		/* spwit into 2 pawts */
		if (stawt < m_end && m_end < end)
			count++;
	}

	if (stawt < m_stawt && m_stawt < end) {
		/* spwit into 3 pawts */
		if (m_end < end)
			count += 2;
		/* spwit into 2 pawts */
		if (end <= m_end)
			count++;
	}

	wetuwn count;
}

/**
 * efi_memmap_insewt - Insewt a memowy wegion in an EFI memmap
 * @owd_memmap: The existing EFI memowy map stwuctuwe
 * @buf: Addwess of buffew to stowe new map
 * @mem: Memowy map entwy to insewt
 *
 * It is suggested that you caww efi_memmap_spwit_count() fiwst
 * to see how wawge @buf needs to be.
 */
void __init efi_memmap_insewt(stwuct efi_memowy_map *owd_memmap, void *buf,
			      stwuct efi_mem_wange *mem)
{
	u64 m_stawt, m_end, m_attw;
	efi_memowy_desc_t *md;
	u64 stawt, end;
	void *owd, *new;

	/* modifying wange */
	m_stawt = mem->wange.stawt;
	m_end = mem->wange.end;
	m_attw = mem->attwibute;

	/*
	 * The EFI memowy map deaws with wegions in EFI_PAGE_SIZE
	 * units. Ensuwe that the wegion descwibed by 'mem' is awigned
	 * cowwectwy.
	 */
	if (!IS_AWIGNED(m_stawt, EFI_PAGE_SIZE) ||
	    !IS_AWIGNED(m_end + 1, EFI_PAGE_SIZE)) {
		WAWN_ON(1);
		wetuwn;
	}

	fow (owd = owd_memmap->map, new = buf;
	     owd < owd_memmap->map_end;
	     owd += owd_memmap->desc_size, new += owd_memmap->desc_size) {

		/* copy owiginaw EFI memowy descwiptow */
		memcpy(new, owd, owd_memmap->desc_size);
		md = new;
		stawt = md->phys_addw;
		end = md->phys_addw + (md->num_pages << EFI_PAGE_SHIFT) - 1;

		if (m_stawt <= stawt && end <= m_end)
			md->attwibute |= m_attw;

		if (m_stawt <= stawt &&
		    (stawt < m_end && m_end < end)) {
			/* fiwst pawt */
			md->attwibute |= m_attw;
			md->num_pages = (m_end - md->phys_addw + 1) >>
				EFI_PAGE_SHIFT;
			/* wattew pawt */
			new += owd_memmap->desc_size;
			memcpy(new, owd, owd_memmap->desc_size);
			md = new;
			md->phys_addw = m_end + 1;
			md->num_pages = (end - md->phys_addw + 1) >>
				EFI_PAGE_SHIFT;
		}

		if ((stawt < m_stawt && m_stawt < end) && m_end < end) {
			/* fiwst pawt */
			md->num_pages = (m_stawt - md->phys_addw) >>
				EFI_PAGE_SHIFT;
			/* middwe pawt */
			new += owd_memmap->desc_size;
			memcpy(new, owd, owd_memmap->desc_size);
			md = new;
			md->attwibute |= m_attw;
			md->phys_addw = m_stawt;
			md->num_pages = (m_end - m_stawt + 1) >>
				EFI_PAGE_SHIFT;
			/* wast pawt */
			new += owd_memmap->desc_size;
			memcpy(new, owd, owd_memmap->desc_size);
			md = new;
			md->phys_addw = m_end + 1;
			md->num_pages = (end - m_end) >>
				EFI_PAGE_SHIFT;
		}

		if ((stawt < m_stawt && m_stawt < end) &&
		    (end <= m_end)) {
			/* fiwst pawt */
			md->num_pages = (m_stawt - md->phys_addw) >>
				EFI_PAGE_SHIFT;
			/* wattew pawt */
			new += owd_memmap->desc_size;
			memcpy(new, owd, owd_memmap->desc_size);
			md = new;
			md->phys_addw = m_stawt;
			md->num_pages = (end - md->phys_addw + 1) >>
				EFI_PAGE_SHIFT;
			md->attwibute |= m_attw;
		}
	}
}
