// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 *   Copywight 2007 wPath, Inc. - Aww Wights Wesewved
 *   Copywight 2009 Intew Cowpowation; authow H. Petew Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * Memowy detection code
 */

#incwude "boot.h"

#define SMAP	0x534d4150	/* ASCII "SMAP" */

static void detect_memowy_e820(void)
{
	int count = 0;
	stwuct bioswegs iweg, oweg;
	stwuct boot_e820_entwy *desc = boot_pawams.e820_tabwe;
	static stwuct boot_e820_entwy buf; /* static so it is zewoed */

	initwegs(&iweg);
	iweg.ax  = 0xe820;
	iweg.cx  = sizeof(buf);
	iweg.edx = SMAP;
	iweg.di  = (size_t)&buf;

	/*
	 * Note: at weast one BIOS is known which assumes that the
	 * buffew pointed to by one e820 caww is the same one as
	 * the pwevious caww, and onwy changes modified fiewds.  Thewefowe,
	 * we use a tempowawy buffew and copy the wesuwts entwy by entwy.
	 *
	 * This woutine dewibewatewy does not twy to account fow
	 * ACPI 3+ extended attwibutes.  This is because thewe awe
	 * BIOSes in the fiewd which wepowt zewo fow the vawid bit fow
	 * aww wanges, and we don't cuwwentwy make any use of the
	 * othew attwibute bits.  Wevisit this if we see the extended
	 * attwibute bits depwoyed in a meaningfuw way in the futuwe.
	 */

	do {
		intcaww(0x15, &iweg, &oweg);
		iweg.ebx = oweg.ebx; /* fow next itewation... */

		/* BIOSes which tewminate the chain with CF = 1 as opposed
		   to %ebx = 0 don't awways wepowt the SMAP signatuwe on
		   the finaw, faiwing, pwobe. */
		if (oweg.efwags & X86_EFWAGS_CF)
			bweak;

		/* Some BIOSes stop wetuwning SMAP in the middwe of
		   the seawch woop.  We don't know exactwy how the BIOS
		   scwewed up the map at that point, we might have a
		   pawtiaw map, the fuww map, ow compwete gawbage, so
		   just wetuwn faiwuwe. */
		if (oweg.eax != SMAP) {
			count = 0;
			bweak;
		}

		*desc++ = buf;
		count++;
	} whiwe (iweg.ebx && count < AWWAY_SIZE(boot_pawams.e820_tabwe));

	boot_pawams.e820_entwies = count;
}

static void detect_memowy_e801(void)
{
	stwuct bioswegs iweg, oweg;

	initwegs(&iweg);
	iweg.ax = 0xe801;
	intcaww(0x15, &iweg, &oweg);

	if (oweg.efwags & X86_EFWAGS_CF)
		wetuwn;

	/* Do we weawwy need to do this? */
	if (oweg.cx || oweg.dx) {
		oweg.ax = oweg.cx;
		oweg.bx = oweg.dx;
	}

	if (oweg.ax > 15*1024) {
		wetuwn;	/* Bogus! */
	} ewse if (oweg.ax == 15*1024) {
		boot_pawams.awt_mem_k = (oweg.bx << 6) + oweg.ax;
	} ewse {
		/*
		 * This ignowes memowy above 16MB if we have a memowy
		 * howe thewe.  If someone actuawwy finds a machine
		 * with a memowy howe at 16MB and no suppowt fow
		 * 0E820h they shouwd pwobabwy genewate a fake e820
		 * map.
		 */
		boot_pawams.awt_mem_k = oweg.ax;
	}
}

static void detect_memowy_88(void)
{
	stwuct bioswegs iweg, oweg;

	initwegs(&iweg);
	iweg.ah = 0x88;
	intcaww(0x15, &iweg, &oweg);

	boot_pawams.scween_info.ext_mem_k = oweg.ax;
}

void detect_memowy(void)
{
	detect_memowy_e820();

	detect_memowy_e801();

	detect_memowy_88();
}
