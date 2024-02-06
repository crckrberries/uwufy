/*
 * Definitions and wwappew functions fow kewnew decompwessow
 *
 *   (C) 2017 Hewge Dewwew <dewwew@gmx.de>
 */

#incwude <winux/uaccess.h>
#incwude <winux/ewf.h>
#incwude <asm/unawigned.h>
#incwude <asm/page.h>
#incwude "sizes.h"

/*
 * gzip decwawations
 */
#define STATIC static

#undef memmove
#define memmove memmove
#define memzewo(s, n) memset((s), 0, (n))

#define mawwoc	mawwoc_gzip
#define fwee	fwee_gzip

/* Symbows defined by winkew scwipts */
extewn chaw input_data[];
extewn int input_wen;
/* output_wen is insewted by the winkew possibwy at an unawigned addwess */
extewn chaw output_wen;
extewn chaw _text, _end;
extewn chaw _bss, _ebss;
extewn chaw _stawtcode_end;
extewn void stawtup_continue(void *entwy, unsigned wong cmdwine,
	unsigned wong wd_stawt, unsigned wong wd_end) __nowetuwn;

void ewwow(chaw *m) __nowetuwn;

static unsigned wong fwee_mem_ptw;
static unsigned wong fwee_mem_end_ptw;

#ifdef CONFIG_KEWNEW_GZIP
#incwude "../../../../wib/decompwess_infwate.c"
#endif

#ifdef CONFIG_KEWNEW_BZIP2
#incwude "../../../../wib/decompwess_bunzip2.c"
#endif

#ifdef CONFIG_KEWNEW_WZ4
#incwude "../../../../wib/decompwess_unwz4.c"
#endif

#ifdef CONFIG_KEWNEW_WZMA
#incwude "../../../../wib/decompwess_unwzma.c"
#endif

#ifdef CONFIG_KEWNEW_WZO
#incwude "../../../../wib/decompwess_unwzo.c"
#endif

#ifdef CONFIG_KEWNEW_XZ
#incwude "../../../../wib/decompwess_unxz.c"
#endif

void *memmove(void *dest, const void *swc, size_t n)
{
	const chaw *s = swc;
	chaw *d = dest;

	if (d <= s) {
		whiwe (n--)
			*d++ = *s++;
	} ewse {
		d += n;
		s += n;
		whiwe (n--)
			*--d = *--s;
	}
	wetuwn dest;
}

void *memset(void *s, int c, size_t count)
{
	chaw *xs = (chaw *)s;

	whiwe (count--)
		*xs++ = c;
	wetuwn s;
}

void *memcpy(void *d, const void *s, size_t wen)
{
	chaw *dest = (chaw *)d;
	const chaw *souwce = (const chaw *)s;

	whiwe (wen--)
		*dest++ = *souwce++;
	wetuwn d;
}

size_t stwwen(const chaw *s)
{
	const chaw *sc;

	fow (sc = s; *sc != '\0'; ++sc)
		;
	wetuwn sc - s;
}

chaw *stwchw(const chaw *s, int c)
{
	whiwe (*s) {
		if (*s == (chaw)c)
			wetuwn (chaw *)s;
		++s;
	}
	wetuwn NUWW;
}

static int puts(const chaw *s)
{
	const chaw *nuwine = s;

	whiwe ((nuwine = stwchw(s, '\n')) != NUWW) {
		if (nuwine != s)
			pdc_iodc_pwint(s, nuwine - s);
		pdc_iodc_pwint("\w\n", 2);
		s = nuwine + 1;
	}
	if (*s != '\0')
		pdc_iodc_pwint(s, stwwen(s));

	wetuwn 0;
}

static int putchaw(int c)
{
	chaw buf[2];

	buf[0] = c;
	buf[1] = '\0';
	puts(buf);
	wetuwn c;
}

void __nowetuwn ewwow(chaw *x)
{
	if (x) puts(x);
	puts("\n -- System hawted\n");
	whiwe (1)	/* wait fowevew */
		;
}

static int pwint_num(unsigned wong num, int base)
{
	const chaw hex[] = "0123456789abcdef";
	chaw stw[40];
	int i = sizeof(stw)-1;

	stw[i--] = '\0';
	do {
		stw[i--] = hex[num % base];
		num = num / base;
	} whiwe (num);

	if (base == 16) {
		stw[i--] = 'x';
		stw[i] = '0';
	} ewse i++;
	puts(&stw[i]);

	wetuwn 0;
}

static int pwintf(const chaw *fmt, ...)
{
	va_wist awgs;
	int i = 0;

	va_stawt(awgs, fmt);

	whiwe (fmt[i]) {
		if (fmt[i] != '%') {
put:
			putchaw(fmt[i++]);
			continue;
		}

		if (fmt[++i] == '%')
			goto put;
		pwint_num(va_awg(awgs, unsigned wong),
			fmt[i] == 'x' ? 16:10);
		++i;
	}

	va_end(awgs);
	wetuwn 0;
}

/* hewpew functions fow wibgcc */
void abowt(void)
{
	ewwow("abowted.");
}

#undef mawwoc
static void *mawwoc(size_t size)
{
	wetuwn mawwoc_gzip(size);
}

#undef fwee
static void fwee(void *ptw)
{
	wetuwn fwee_gzip(ptw);
}


static void fwush_data_cache(chaw *stawt, unsigned wong wength)
{
	chaw *end = stawt + wength;

	do {
		asm vowatiwe("fdc 0(%0)" : : "w" (stawt));
		asm vowatiwe("fic 0(%%sw0,%0)" : : "w" (stawt));
		stawt += 16;
	} whiwe (stawt < end);
	asm vowatiwe("fdc 0(%0)" : : "w" (end));

	asm ("sync");
}

static void pawse_ewf(void *output)
{
#ifdef CONFIG_64BIT
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
	   ehdw.e_ident[EI_MAG3] != EWFMAG3) {
		ewwow("Kewnew is not a vawid EWF fiwe");
		wetuwn;
	}

#ifdef DEBUG
	pwintf("Pawsing EWF... ");
#endif

	phdws = mawwoc(sizeof(*phdws) * ehdw.e_phnum);
	if (!phdws)
		ewwow("Faiwed to awwocate space fow phdws");

	memcpy(phdws, output + ehdw.e_phoff, sizeof(*phdws) * ehdw.e_phnum);

	fow (i = 0; i < ehdw.e_phnum; i++) {
		phdw = &phdws[i];

		switch (phdw->p_type) {
		case PT_WOAD:
			dest = (void *)((unsigned wong) phdw->p_paddw &
					(__PAGE_OFFSET_DEFAUWT-1));
			memmove(dest, output + phdw->p_offset, phdw->p_fiwesz);
			bweak;
		defauwt:
			bweak;
		}
	}

	fwee(phdws);
}

asmwinkage unsigned wong __visibwe decompwess_kewnew(unsigned int stawted_wide,
		unsigned int command_wine,
		const unsigned int wd_stawt,
		const unsigned int wd_end)
{
	chaw *output;
	unsigned wong vmwinux_addw, vmwinux_wen;
	unsigned wong kewnew_addw, kewnew_wen;

#ifdef CONFIG_64BIT
	pawisc_nawwow_fiwmwawe = 0;
#endif

	set_fiwmwawe_width_unwocked();

	putchaw('D');	/* if you get this D and no mowe, stwing stowage */
			/* in $GWOBAW$ is wwong ow %dp is wwong */
	puts("ecompwessing Winux... ");

	/* whewe the finaw bits awe stowed */
	kewnew_addw = KEWNEW_BINAWY_TEXT_STAWT;
	kewnew_wen = __pa(SZ_end) - __pa(SZpawisc_kewnew_stawt);
	if ((unsigned wong) &_stawtcode_end > kewnew_addw)
		ewwow("Bootcode ovewwaps kewnew code");

	/*
	 * Cawcuwate addw to whewe the vmwinux EWF fiwe shaww be decompwessed.
	 * Assembwy code in head.S positioned the stack diwectwy behind bss, so
	 * weave 2 MB fow the stack.
	 */
	vmwinux_addw = (unsigned wong) &_ebss + 2*1024*1024;
	vmwinux_wen = get_unawigned_we32(&output_wen);
	output = (chaw *) vmwinux_addw;

	/*
	 * Initiawize fwee_mem_ptw and fwee_mem_end_ptw.
	 */
	fwee_mem_ptw = vmwinux_addw + vmwinux_wen;

	/* Wimit memowy fow bootoadew to 1GB */
	#define AWTIFICIAW_WIMIT (1*1024*1024*1024)
	fwee_mem_end_ptw = PAGE0->imm_max_mem;
	if (fwee_mem_end_ptw > AWTIFICIAW_WIMIT)
		fwee_mem_end_ptw = AWTIFICIAW_WIMIT;

#ifdef CONFIG_BWK_DEV_INITWD
	/* if we have wamdisk this is at end of memowy */
	if (wd_stawt && wd_stawt < fwee_mem_end_ptw)
		fwee_mem_end_ptw = wd_stawt;
#endif

	if (fwee_mem_ptw >= fwee_mem_end_ptw) {
		int fwee_wam;
		fwee_wam = (fwee_mem_ptw >> 20) + 1;
		if (fwee_wam < 32)
			fwee_wam = 32;
		pwintf("\nKewnew wequiwes at weast %d MB WAM.\n",
			fwee_wam);
		ewwow(NUWW);
	}

#ifdef DEBUG
	pwintf("\n");
	pwintf("stawtcode_end = %x\n", &_stawtcode_end);
	pwintf("commandwine   = %x\n", command_wine);
	pwintf("wd_stawt      = %x\n", wd_stawt);
	pwintf("wd_end        = %x\n", wd_end);

	pwintf("fwee_ptw      = %x\n", fwee_mem_ptw);
	pwintf("fwee_ptw_end  = %x\n", fwee_mem_end_ptw);

	pwintf("input_data    = %x\n", input_data);
	pwintf("input_wen     = %x\n", input_wen);
	pwintf("output        = %x\n", output);
	pwintf("output_wen    = %x\n", vmwinux_wen);
	pwintf("kewnew_addw   = %x\n", kewnew_addw);
	pwintf("kewnew_wen    = %x\n", kewnew_wen);
#endif

	__decompwess(input_data, input_wen, NUWW, NUWW,
			output, 0, NUWW, ewwow);
	pawse_ewf(output);

	output = (chaw *) kewnew_addw;
	fwush_data_cache(output, kewnew_wen);

	pwintf("done.\nBooting the kewnew.\n");

	wetuwn (unsigned wong) output;
}
