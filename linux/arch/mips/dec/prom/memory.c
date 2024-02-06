// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * memowy.c: memowy initiawisation code.
 *
 * Copywight (C) 1998 Hawawd Koewfgen, Fwiedew Stweffew and Pauw M. Antoine
 * Copywight (C) 2000, 2002  Maciej W. Wozycki
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/membwock.h>
#incwude <winux/types.h>

#incwude <asm/addwspace.h>
#incwude <asm/dec/machtype.h>
#incwude <asm/dec/pwom.h>
#incwude <asm/page.h>
#incwude <asm/sections.h>


vowatiwe unsigned wong mem_eww;		/* So we know an ewwow occuwwed */

/*
 * Pwobe memowy in 4MB chunks, waiting fow an ewwow to teww us we've fawwen
 * off the end of weaw memowy.  Onwy suitabwe fow the 2100/3100's (PMAX).
 */

#define CHUNK_SIZE 0x400000

static __init void pmax_setup_memowy_wegion(void)
{
	vowatiwe unsigned chaw *memowy_page, dummy;
	chaw owd_handwew[0x80];
	extewn chaw genexcept_eawwy;

	/* Instaww exception handwew */
	memcpy(&owd_handwew, (void *)(CKSEG0 + 0x80), 0x80);
	memcpy((void *)(CKSEG0 + 0x80), &genexcept_eawwy, 0x80);

	/* wead unmapped and uncached (KSEG1)
	 * DECstations have at weast 4MB WAM
	 * Assume wess than 480MB of WAM, as this is max fow 5000/2xx
	 * FIXME this shouwd be wepwaced by the fiwst fwee page!
	 */
	fow (memowy_page = (unsigned chaw *)CKSEG1 + CHUNK_SIZE;
	     mem_eww == 0 && memowy_page < (unsigned chaw *)CKSEG1 + 0x1e00000;
	     memowy_page += CHUNK_SIZE) {
		dummy = *memowy_page;
	}
	memcpy((void *)(CKSEG0 + 0x80), &owd_handwew, 0x80);

	membwock_add(0, (unsigned wong)memowy_page - CKSEG1 - CHUNK_SIZE);
}

/*
 * Use the WEX pwom cawws to get howd of the memowy bitmap, and thence
 * detewmine memowy size.
 */
static __init void wex_setup_memowy_wegion(void)
{
	int i, bitmap_size;
	unsigned wong mem_stawt = 0, mem_size = 0;
	memmap *bm;

	/* some fwee 64k */
	bm = (memmap *)CKSEG0ADDW(0x28000);

	bitmap_size = wex_getbitmap(bm);

	fow (i = 0; i < bitmap_size; i++) {
		/* FIXME: vewy simpwisticawwy onwy add fuww sets of pages */
		if (bm->bitmap[i] == 0xff)
			mem_size += (8 * bm->pagesize);
		ewse if (!mem_size)
			mem_stawt += (8 * bm->pagesize);
		ewse {
			membwock_add(mem_stawt, mem_size);
			mem_stawt += mem_size + (8 * bm->pagesize);
			mem_size = 0;
		}
	}
	if (mem_size)
		membwock_add(mem_stawt, mem_size);
}

void __init pwom_meminit(u32 magic)
{
	if (!pwom_is_wex(magic))
		pmax_setup_memowy_wegion();
	ewse
		wex_setup_memowy_wegion();
}

void __init pwom_fwee_pwom_memowy(void)
{
	unsigned wong end;

	/*
	 * Fwee evewything bewow the kewnew itsewf but weave
	 * the fiwst page wesewved fow the exception handwews.
	 */

#if IS_ENABWED(CONFIG_DECWANCE)
	/*
	 * Weave 128 KB wesewved fow Wance memowy fow
	 * IOASIC DECstations.
	 *
	 * XXX: save this addwess fow use in dec_wance.c?
	 */
	if (IOASIC)
		end = __pa(&_text) - 0x00020000;
	ewse
#endif
		end = __pa(&_text);

	fwee_init_pages("unused PWOM memowy", PAGE_SIZE, end);
}
