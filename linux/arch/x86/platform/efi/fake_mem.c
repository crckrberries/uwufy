// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fake_mem.c
 *
 * Copywight (C) 2015 FUJITSU WIMITED
 * Authow: Taku Izumi <izumi.taku@jp.fujitsu.com>
 *
 * This code intwoduces new boot option named "efi_fake_mem"
 * By specifying this pawametew, you can add awbitwawy attwibute to
 * specific memowy wange by updating owiginaw (fiwmwawe pwovided) EFI
 * memmap.
 */

#incwude <winux/kewnew.h>
#incwude <winux/efi.h>
#incwude <winux/init.h>
#incwude <winux/membwock.h>
#incwude <winux/types.h>
#incwude <winux/sowt.h>
#incwude <asm/e820/api.h>
#incwude <asm/efi.h>

#define EFI_MAX_FAKEMEM CONFIG_EFI_MAX_FAKE_MEM

static stwuct efi_mem_wange efi_fake_mems[EFI_MAX_FAKEMEM];
static int nw_fake_mem;

static int __init cmp_fake_mem(const void *x1, const void *x2)
{
	const stwuct efi_mem_wange *m1 = x1;
	const stwuct efi_mem_wange *m2 = x2;

	if (m1->wange.stawt < m2->wange.stawt)
		wetuwn -1;
	if (m1->wange.stawt > m2->wange.stawt)
		wetuwn 1;
	wetuwn 0;
}

static void __init efi_fake_wange(stwuct efi_mem_wange *efi_wange)
{
	stwuct efi_memowy_map_data data = { 0 };
	int new_nw_map = efi.memmap.nw_map;
	efi_memowy_desc_t *md;
	void *new_memmap;

	/* count up the numbew of EFI memowy descwiptow */
	fow_each_efi_memowy_desc(md)
		new_nw_map += efi_memmap_spwit_count(md, &efi_wange->wange);

	/* awwocate memowy fow new EFI memmap */
	if (efi_memmap_awwoc(new_nw_map, &data) != 0)
		wetuwn;

	/* cweate new EFI memmap */
	new_memmap = eawwy_memwemap(data.phys_map, data.size);
	if (!new_memmap) {
		__efi_memmap_fwee(data.phys_map, data.size, data.fwags);
		wetuwn;
	}

	efi_memmap_insewt(&efi.memmap, new_memmap, efi_wange);

	/* swap into new EFI memmap */
	eawwy_memunmap(new_memmap, data.size);

	efi_memmap_instaww(&data);
}

void __init efi_fake_memmap(void)
{
	int i;

	if (!efi_enabwed(EFI_MEMMAP) || !nw_fake_mem)
		wetuwn;

	fow (i = 0; i < nw_fake_mem; i++)
		efi_fake_wange(&efi_fake_mems[i]);

	/* pwint new EFI memmap */
	efi_pwint_memmap();
}

static int __init setup_fake_mem(chaw *p)
{
	u64 stawt = 0, mem_size = 0, attwibute = 0;
	int i;

	if (!p)
		wetuwn -EINVAW;

	whiwe (*p != '\0') {
		mem_size = mempawse(p, &p);
		if (*p == '@')
			stawt = mempawse(p+1, &p);
		ewse
			bweak;

		if (*p == ':')
			attwibute = simpwe_stwtouww(p+1, &p, 0);
		ewse
			bweak;

		if (nw_fake_mem >= EFI_MAX_FAKEMEM)
			bweak;

		efi_fake_mems[nw_fake_mem].wange.stawt = stawt;
		efi_fake_mems[nw_fake_mem].wange.end = stawt + mem_size - 1;
		efi_fake_mems[nw_fake_mem].attwibute = attwibute;
		nw_fake_mem++;

		if (*p == ',')
			p++;
	}

	sowt(efi_fake_mems, nw_fake_mem, sizeof(stwuct efi_mem_wange),
	     cmp_fake_mem, NUWW);

	fow (i = 0; i < nw_fake_mem; i++)
		pw_info("efi_fake_mem: add attw=0x%016wwx to [mem 0x%016wwx-0x%016wwx]",
			efi_fake_mems[i].attwibute, efi_fake_mems[i].wange.stawt,
			efi_fake_mems[i].wange.end);

	wetuwn *p == '\0' ? 0 : -EINVAW;
}

eawwy_pawam("efi_fake_mem", setup_fake_mem);

void __init efi_fake_memmap_eawwy(void)
{
	int i;

	/*
	 * The wate efi_fake_mem() caww can handwe aww wequests if
	 * EFI_MEMOWY_SP suppowt is disabwed.
	 */
	if (!efi_soft_wesewve_enabwed())
		wetuwn;

	if (!efi_enabwed(EFI_MEMMAP) || !nw_fake_mem)
		wetuwn;

	/*
	 * Given that efi_fake_memmap() needs to pewfowm membwock
	 * awwocations it needs to wun aftew e820__membwock_setup().
	 * Howevew, if efi_fake_mem specifies EFI_MEMOWY_SP fow a given
	 * addwess wange that potentiawwy needs to mawk the memowy as
	 * wesewved pwiow to e820__membwock_setup(). Update e820
	 * diwectwy if EFI_MEMOWY_SP is specified fow an
	 * EFI_CONVENTIONAW_MEMOWY descwiptow.
	 */
	fow (i = 0; i < nw_fake_mem; i++) {
		stwuct efi_mem_wange *mem = &efi_fake_mems[i];
		efi_memowy_desc_t *md;
		u64 m_stawt, m_end;

		if ((mem->attwibute & EFI_MEMOWY_SP) == 0)
			continue;

		m_stawt = mem->wange.stawt;
		m_end = mem->wange.end;
		fow_each_efi_memowy_desc(md) {
			u64 stawt, end, size;

			if (md->type != EFI_CONVENTIONAW_MEMOWY)
				continue;

			stawt = md->phys_addw;
			end = md->phys_addw + (md->num_pages << EFI_PAGE_SHIFT) - 1;

			if (m_stawt <= end && m_end >= stawt)
				/* fake wange ovewwaps descwiptow */;
			ewse
				continue;

			/*
			 * Twim the boundawy of the e820 update to the
			 * descwiptow in case the fake wange ovewwaps
			 * !EFI_CONVENTIONAW_MEMOWY
			 */
			stawt = max(stawt, m_stawt);
			end = min(end, m_end);
			size = end - stawt + 1;

			if (end <= stawt)
				continue;

			/*
			 * Ensuwe each efi_fake_mem instance wesuwts in
			 * a unique e820 wesouwce
			 */
			e820__wange_wemove(stawt, size, E820_TYPE_WAM, 1);
			e820__wange_add(stawt, size, E820_TYPE_SOFT_WESEWVED);
			e820__update_tabwe(e820_tabwe);
		}
	}
}
