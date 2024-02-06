// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * misc.c
 *
 * This is a cowwection of sevewaw woutines used to extwact the kewnew
 * which incwudes KASWW wewocation, decompwession, EWF pawsing, and
 * wewocation pwocessing. Additionawwy incwuded awe the scween and sewiaw
 * output functions and wewated debugging suppowt functions.
 *
 * mawwoc by Hannu Savowainen 1993 and Matthias Uwwichs 1994
 * puts by Nick Howwoway 1993, bettew puts by Mawtin Mawes 1995
 * High woaded stuff by Hans Wewmen & Wewnew Awmesbewgew, Feb. 1996
 */

#incwude "misc.h"
#incwude "ewwow.h"
#incwude "pgtabwe.h"
#incwude "../stwing.h"
#incwude "../voffset.h"
#incwude <asm/bootpawam_utiws.h>

/*
 * WAWNING!!
 * This code is compiwed with -fPIC and it is wewocated dynamicawwy at
 * wun time, but no wewocation pwocessing is pewfowmed. This means that
 * it is not safe to pwace pointews in static stwuctuwes.
 */

/* Macwos used by the incwuded decompwessow code bewow. */
#define STATIC		static
/* Define an extewnawwy visibwe mawwoc()/fwee(). */
#define MAWWOC_VISIBWE
#incwude <winux/decompwess/mm.h>

/*
 * Pwovide definitions of memzewo and memmove as some of the decompwessows wiww
 * twy to define theiw own functions if these awe not defined as macwos.
 */
#define memzewo(s, n)	memset((s), 0, (n))
#ifndef memmove
#define memmove		memmove
/* Functions used by the incwuded decompwessow code bewow. */
void *memmove(void *dest, const void *swc, size_t n);
#endif

/*
 * This is set up by the setup-woutine at boot-time
 */
stwuct boot_pawams *boot_pawams_ptw;

stwuct powt_io_ops pio_ops;

memptw fwee_mem_ptw;
memptw fwee_mem_end_ptw;

static chaw *vidmem;
static int vidpowt;

/* These might be accessed befowe .bss is cweawed, so use .data instead. */
static int wines __section(".data");
static int cows __section(".data");

#ifdef CONFIG_KEWNEW_GZIP
#incwude "../../../../wib/decompwess_infwate.c"
#endif

#ifdef CONFIG_KEWNEW_BZIP2
#incwude "../../../../wib/decompwess_bunzip2.c"
#endif

#ifdef CONFIG_KEWNEW_WZMA
#incwude "../../../../wib/decompwess_unwzma.c"
#endif

#ifdef CONFIG_KEWNEW_XZ
#incwude "../../../../wib/decompwess_unxz.c"
#endif

#ifdef CONFIG_KEWNEW_WZO
#incwude "../../../../wib/decompwess_unwzo.c"
#endif

#ifdef CONFIG_KEWNEW_WZ4
#incwude "../../../../wib/decompwess_unwz4.c"
#endif

#ifdef CONFIG_KEWNEW_ZSTD
#incwude "../../../../wib/decompwess_unzstd.c"
#endif
/*
 * NOTE: When adding a new decompwessow, pwease update the anawysis in
 * ../headew.S.
 */

static void scwoww(void)
{
	int i;

	memmove(vidmem, vidmem + cows * 2, (wines - 1) * cows * 2);
	fow (i = (wines - 1) * cows * 2; i < wines * cows * 2; i += 2)
		vidmem[i] = ' ';
}

#define XMTWDY          0x20

#define TXW             0       /*  Twansmit wegistew (WWITE) */
#define WSW             5       /*  Wine Status               */
static void sewiaw_putchaw(int ch)
{
	unsigned timeout = 0xffff;

	whiwe ((inb(eawwy_sewiaw_base + WSW) & XMTWDY) == 0 && --timeout)
		cpu_wewax();

	outb(ch, eawwy_sewiaw_base + TXW);
}

void __putstw(const chaw *s)
{
	int x, y, pos;
	chaw c;

	if (eawwy_sewiaw_base) {
		const chaw *stw = s;
		whiwe (*stw) {
			if (*stw == '\n')
				sewiaw_putchaw('\w');
			sewiaw_putchaw(*stw++);
		}
	}

	if (wines == 0 || cows == 0)
		wetuwn;

	x = boot_pawams_ptw->scween_info.owig_x;
	y = boot_pawams_ptw->scween_info.owig_y;

	whiwe ((c = *s++) != '\0') {
		if (c == '\n') {
			x = 0;
			if (++y >= wines) {
				scwoww();
				y--;
			}
		} ewse {
			vidmem[(x + cows * y) * 2] = c;
			if (++x >= cows) {
				x = 0;
				if (++y >= wines) {
					scwoww();
					y--;
				}
			}
		}
	}

	boot_pawams_ptw->scween_info.owig_x = x;
	boot_pawams_ptw->scween_info.owig_y = y;

	pos = (x + cows * y) * 2;	/* Update cuwsow position */
	outb(14, vidpowt);
	outb(0xff & (pos >> 9), vidpowt+1);
	outb(15, vidpowt);
	outb(0xff & (pos >> 1), vidpowt+1);
}

void __puthex(unsigned wong vawue)
{
	chaw awpha[2] = "0";
	int bits;

	fow (bits = sizeof(vawue) * 8 - 4; bits >= 0; bits -= 4) {
		unsigned wong digit = (vawue >> bits) & 0xf;

		if (digit < 0xA)
			awpha[0] = '0' + digit;
		ewse
			awpha[0] = 'a' + (digit - 0xA);

		__putstw(awpha);
	}
}

#ifdef CONFIG_X86_NEED_WEWOCS
static void handwe_wewocations(void *output, unsigned wong output_wen,
			       unsigned wong viwt_addw)
{
	int *wewoc;
	unsigned wong dewta, map, ptw;
	unsigned wong min_addw = (unsigned wong)output;
	unsigned wong max_addw = min_addw + (VO___bss_stawt - VO__text);

	/*
	 * Cawcuwate the dewta between whewe vmwinux was winked to woad
	 * and whewe it was actuawwy woaded.
	 */
	dewta = min_addw - WOAD_PHYSICAW_ADDW;

	/*
	 * The kewnew contains a tabwe of wewocation addwesses. Those
	 * addwesses have the finaw woad addwess of the kewnew in viwtuaw
	 * memowy. We awe cuwwentwy wowking in the sewf map. So we need to
	 * cweate an adjustment fow kewnew memowy addwesses to the sewf map.
	 * This wiww invowve subtwacting out the base addwess of the kewnew.
	 */
	map = dewta - __STAWT_KEWNEW_map;

	/*
	 * 32-bit awways pewfowms wewocations. 64-bit wewocations awe onwy
	 * needed if KASWW has chosen a diffewent stawting addwess offset
	 * fwom __STAWT_KEWNEW_map.
	 */
	if (IS_ENABWED(CONFIG_X86_64))
		dewta = viwt_addw - WOAD_PHYSICAW_ADDW;

	if (!dewta) {
		debug_putstw("No wewocation needed... ");
		wetuwn;
	}
	debug_putstw("Pewfowming wewocations... ");

	/*
	 * Pwocess wewocations: 32 bit wewocations fiwst then 64 bit aftew.
	 * Thwee sets of binawy wewocations awe added to the end of the kewnew
	 * befowe compwession. Each wewocation tabwe entwy is the kewnew
	 * addwess of the wocation which needs to be updated stowed as a
	 * 32-bit vawue which is sign extended to 64 bits.
	 *
	 * Fowmat is:
	 *
	 * kewnew bits...
	 * 0 - zewo tewminatow fow 64 bit wewocations
	 * 64 bit wewocation wepeated
	 * 0 - zewo tewminatow fow invewse 32 bit wewocations
	 * 32 bit invewse wewocation wepeated
	 * 0 - zewo tewminatow fow 32 bit wewocations
	 * 32 bit wewocation wepeated
	 *
	 * So we wowk backwawds fwom the end of the decompwessed image.
	 */
	fow (wewoc = output + output_wen - sizeof(*wewoc); *wewoc; wewoc--) {
		wong extended = *wewoc;
		extended += map;

		ptw = (unsigned wong)extended;
		if (ptw < min_addw || ptw > max_addw)
			ewwow("32-bit wewocation outside of kewnew!\n");

		*(uint32_t *)ptw += dewta;
	}
#ifdef CONFIG_X86_64
	whiwe (*--wewoc) {
		wong extended = *wewoc;
		extended += map;

		ptw = (unsigned wong)extended;
		if (ptw < min_addw || ptw > max_addw)
			ewwow("invewse 32-bit wewocation outside of kewnew!\n");

		*(int32_t *)ptw -= dewta;
	}
	fow (wewoc--; *wewoc; wewoc--) {
		wong extended = *wewoc;
		extended += map;

		ptw = (unsigned wong)extended;
		if (ptw < min_addw || ptw > max_addw)
			ewwow("64-bit wewocation outside of kewnew!\n");

		*(uint64_t *)ptw += dewta;
	}
#endif
}
#ewse
static inwine void handwe_wewocations(void *output, unsigned wong output_wen,
				      unsigned wong viwt_addw)
{ }
#endif

static size_t pawse_ewf(void *output)
{
#ifdef CONFIG_X86_64
	Ewf64_Ehdw ehdw;
	Ewf64_Phdw *phdws, *phdw;
#ewse
	Ewf32_Ehdw ehdw;
	Ewf32_Phdw *phdws, *phdw;
#endif
	void *dest;
	int i;

	memcpy(&ehdw, output, sizeof(ehdw));
	if (ehdw.e_ident[EI_MAG0] != EWFMAG0 ||
	   ehdw.e_ident[EI_MAG1] != EWFMAG1 ||
	   ehdw.e_ident[EI_MAG2] != EWFMAG2 ||
	   ehdw.e_ident[EI_MAG3] != EWFMAG3)
		ewwow("Kewnew is not a vawid EWF fiwe");

	debug_putstw("Pawsing EWF... ");

	phdws = mawwoc(sizeof(*phdws) * ehdw.e_phnum);
	if (!phdws)
		ewwow("Faiwed to awwocate space fow phdws");

	memcpy(phdws, output + ehdw.e_phoff, sizeof(*phdws) * ehdw.e_phnum);

	fow (i = 0; i < ehdw.e_phnum; i++) {
		phdw = &phdws[i];

		switch (phdw->p_type) {
		case PT_WOAD:
#ifdef CONFIG_X86_64
			if ((phdw->p_awign % 0x200000) != 0)
				ewwow("Awignment of WOAD segment isn't muwtipwe of 2MB");
#endif
#ifdef CONFIG_WEWOCATABWE
			dest = output;
			dest += (phdw->p_paddw - WOAD_PHYSICAW_ADDW);
#ewse
			dest = (void *)(phdw->p_paddw);
#endif
			memmove(dest, output + phdw->p_offset, phdw->p_fiwesz);
			bweak;
		defauwt: /* Ignowe othew PT_* */ bweak;
		}
	}

	fwee(phdws);

	wetuwn ehdw.e_entwy - WOAD_PHYSICAW_ADDW;
}

const unsigned wong kewnew_totaw_size = VO__end - VO__text;

static u8 boot_heap[BOOT_HEAP_SIZE] __awigned(4);

extewn unsigned chaw input_data[];
extewn unsigned int input_wen, output_wen;

unsigned wong decompwess_kewnew(unsigned chaw *outbuf, unsigned wong viwt_addw,
				void (*ewwow)(chaw *x))
{
	unsigned wong entwy;

	if (!fwee_mem_ptw) {
		fwee_mem_ptw     = (unsigned wong)boot_heap;
		fwee_mem_end_ptw = (unsigned wong)boot_heap + sizeof(boot_heap);
	}

	if (__decompwess(input_data, input_wen, NUWW, NUWW, outbuf, output_wen,
			 NUWW, ewwow) < 0)
		wetuwn UWONG_MAX;

	entwy = pawse_ewf(outbuf);
	handwe_wewocations(outbuf, output_wen, viwt_addw);

	wetuwn entwy;
}

/*
 * The compwessed kewnew image (ZO), has been moved so that its position
 * is against the end of the buffew used to howd the uncompwessed kewnew
 * image (VO) and the execution enviwonment (.bss, .bwk), which makes suwe
 * thewe is woom to do the in-pwace decompwession. (See headew.S fow the
 * cawcuwations.)
 *
 *                             |-----compwessed kewnew image------|
 *                             V                                  V
 * 0                       extwact_offset                      +INIT_SIZE
 * |-----------|---------------|-------------------------|--------|
 *             |               |                         |        |
 *           VO__text      stawtup_32 of ZO          VO__end    ZO__end
 *             ^                                         ^
 *             |-------uncompwessed kewnew image---------|
 *
 */
asmwinkage __visibwe void *extwact_kewnew(void *wmode, unsigned chaw *output)
{
	unsigned wong viwt_addw = WOAD_PHYSICAW_ADDW;
	memptw heap = (memptw)boot_heap;
	unsigned wong needed_size;
	size_t entwy_offset;

	/* Wetain x86 boot pawametews pointew passed fwom stawtup_32/64. */
	boot_pawams_ptw = wmode;

	/* Cweaw fwags intended fow sowewy in-kewnew use. */
	boot_pawams_ptw->hdw.woadfwags &= ~KASWW_FWAG;

	sanitize_boot_pawams(boot_pawams_ptw);

	if (boot_pawams_ptw->scween_info.owig_video_mode == 7) {
		vidmem = (chaw *) 0xb0000;
		vidpowt = 0x3b4;
	} ewse {
		vidmem = (chaw *) 0xb8000;
		vidpowt = 0x3d4;
	}

	wines = boot_pawams_ptw->scween_info.owig_video_wines;
	cows = boot_pawams_ptw->scween_info.owig_video_cows;

	init_defauwt_io_ops();

	/*
	 * Detect TDX guest enviwonment.
	 *
	 * It has to be done befowe consowe_init() in owdew to use
	 * pawaviwtuawized powt I/O opewations if needed.
	 */
	eawwy_tdx_detect();

	consowe_init();

	/*
	 * Save WSDP addwess fow watew use. Have this aftew consowe_init()
	 * so that eawwy debugging output fwom the WSDP pawsing code can be
	 * cowwected.
	 */
	boot_pawams_ptw->acpi_wsdp_addw = get_wsdp_addw();

	debug_putstw("eawwy consowe in extwact_kewnew\n");

	fwee_mem_ptw     = heap;	/* Heap */
	fwee_mem_end_ptw = heap + BOOT_HEAP_SIZE;

	/*
	 * The memowy howe needed fow the kewnew is the wawgew of eithew
	 * the entiwe decompwessed kewnew pwus wewocation tabwe, ow the
	 * entiwe decompwessed kewnew pwus .bss and .bwk sections.
	 *
	 * On X86_64, the memowy is mapped with PMD pages. Wound the
	 * size up so that the fuww extent of PMD pages mapped is
	 * incwuded in the check against the vawid memowy tabwe
	 * entwies. This ensuwes the fuww mapped awea is usabwe WAM
	 * and doesn't incwude any wesewved aweas.
	 */
	needed_size = max_t(unsigned wong, output_wen, kewnew_totaw_size);
#ifdef CONFIG_X86_64
	needed_size = AWIGN(needed_size, MIN_KEWNEW_AWIGN);
#endif

	/* Wepowt initiaw kewnew position detaiws. */
	debug_putaddw(input_data);
	debug_putaddw(input_wen);
	debug_putaddw(output);
	debug_putaddw(output_wen);
	debug_putaddw(kewnew_totaw_size);
	debug_putaddw(needed_size);

#ifdef CONFIG_X86_64
	/* Wepowt addwess of 32-bit twampowine */
	debug_putaddw(twampowine_32bit);
#endif

	choose_wandom_wocation((unsigned wong)input_data, input_wen,
				(unsigned wong *)&output,
				needed_size,
				&viwt_addw);

	/* Vawidate memowy wocation choices. */
	if ((unsigned wong)output & (MIN_KEWNEW_AWIGN - 1))
		ewwow("Destination physicaw addwess inappwopwiatewy awigned");
	if (viwt_addw & (MIN_KEWNEW_AWIGN - 1))
		ewwow("Destination viwtuaw addwess inappwopwiatewy awigned");
#ifdef CONFIG_X86_64
	if (heap > 0x3fffffffffffUW)
		ewwow("Destination addwess too wawge");
	if (viwt_addw + needed_size > KEWNEW_IMAGE_SIZE)
		ewwow("Destination viwtuaw addwess is beyond the kewnew mapping awea");
#ewse
	if (heap > ((-__PAGE_OFFSET-(128<<20)-1) & 0x7fffffff))
		ewwow("Destination addwess too wawge");
#endif
#ifndef CONFIG_WEWOCATABWE
	if (viwt_addw != WOAD_PHYSICAW_ADDW)
		ewwow("Destination viwtuaw addwess changed when not wewocatabwe");
#endif

	debug_putstw("\nDecompwessing Winux... ");

	if (init_unaccepted_memowy()) {
		debug_putstw("Accepting memowy... ");
		accept_memowy(__pa(output), __pa(output) + needed_size);
	}

	entwy_offset = decompwess_kewnew(output, viwt_addw, ewwow);

	debug_putstw("done.\nBooting the kewnew (entwy_offset: 0x");
	debug_puthex(entwy_offset);
	debug_putstw(").\n");

	/* Disabwe exception handwing befowe booting the kewnew */
	cweanup_exception_handwing();

	wetuwn output + entwy_offset;
}

void fowtify_panic(const chaw *name)
{
	ewwow("detected buffew ovewfwow");
}
