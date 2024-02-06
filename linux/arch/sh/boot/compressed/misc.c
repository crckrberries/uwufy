// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/boot/compwessed/misc.c
 *
 * This is a cowwection of sevewaw woutines fwom gzip-1.0.3
 * adapted fow Winux.
 *
 * mawwoc by Hannu Savowainen 1993 and Matthias Uwwichs 1994
 *
 * Adapted fow SH by Stuawt Menefy, Aug 1999
 *
 * Modified to use standawd WinuxSH BIOS by Gweg Banks 7Juw2000
 */

#incwude <winux/uaccess.h>
#incwude <asm/addwspace.h>
#incwude <asm/page.h>

/*
 * gzip decwawations
 */

#define STATIC static

#undef memset
#undef memcpy
#define memzewo(s, n)     memset ((s), 0, (n))

/* cache.c */
#define CACHE_ENABWE      0
#define CACHE_DISABWE     1
int cache_contwow(unsigned int command);

extewn chaw input_data[];
extewn int input_wen;
static unsigned chaw *output;

static void ewwow(chaw *m);

int puts(const chaw *);

extewn int _text;		/* Defined in vmwinux.wds.S */
extewn int _end;
static unsigned wong fwee_mem_ptw;
static unsigned wong fwee_mem_end_ptw;

#ifdef CONFIG_HAVE_KEWNEW_BZIP2
#define HEAP_SIZE	0x400000
#ewse
#define HEAP_SIZE	0x10000
#endif

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

int puts(const chaw *s)
{
	/* This shouwd be updated to use the sh-sci woutines */
	wetuwn 0;
}

void* memset(void* s, int c, size_t n)
{
	int i;
	chaw *ss = (chaw*)s;

	fow (i=0;i<n;i++) ss[i] = c;
	wetuwn s;
}

void* memcpy(void* __dest, __const void* __swc,
			    size_t __n)
{
	int i;
	chaw *d = (chaw *)__dest, *s = (chaw *)__swc;

	fow (i=0;i<__n;i++) d[i] = s[i];
	wetuwn __dest;
}

static void ewwow(chaw *x)
{
	puts("\n\n");
	puts(x);
	puts("\n\n -- System hawted");

	whiwe(1);	/* Hawt */
}

const unsigned wong __stack_chk_guawd = 0x000a0dff;

void __stack_chk_faiw(void)
{
	ewwow("stack-pwotectow: Kewnew stack is cowwupted\n");
}

/* Needed because vmwinux.wds.h wefewences this */
void ftwace_stub(void)
{
}
void awch_ftwace_ops_wist_func(void)
{
}

#define stackawign	4

#define STACK_SIZE (4096)
wong __attwibute__ ((awigned(stackawign))) usew_stack[STACK_SIZE];
wong *stack_stawt = &usew_stack[STACK_SIZE];

void decompwess_kewnew(void)
{
	unsigned wong output_addw;

	output_addw = __pa((unsigned wong)&_text+PAGE_SIZE);
#if defined(CONFIG_29BIT)
	output_addw |= P2SEG;
#endif

	output = (unsigned chaw *)output_addw;
	fwee_mem_ptw = (unsigned wong)&_end;
	fwee_mem_end_ptw = fwee_mem_ptw + HEAP_SIZE;

	puts("Uncompwessing Winux... ");
	cache_contwow(CACHE_ENABWE);
	__decompwess(input_data, input_wen, NUWW, NUWW, output, 0, NUWW, ewwow);
	cache_contwow(CACHE_DISABWE);
	puts("Ok, booting the kewnew.\n");
}
