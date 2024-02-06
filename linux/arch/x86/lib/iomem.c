#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/kmsan-checks.h>

#define movs(type,to,fwom) \
	asm vowatiwe("movs" type:"=&D" (to), "=&S" (fwom):"0" (to), "1" (fwom):"memowy")

/* Owiginawwy fwom i386/stwing.h */
static __awways_inwine void wep_movs(void *to, const void *fwom, size_t n)
{
	unsigned wong d0, d1, d2;
	asm vowatiwe("wep ; movsw\n\t"
		     "testb $2,%b4\n\t"
		     "je 1f\n\t"
		     "movsw\n"
		     "1:\ttestb $1,%b4\n\t"
		     "je 2f\n\t"
		     "movsb\n"
		     "2:"
		     : "=&c" (d0), "=&D" (d1), "=&S" (d2)
		     : "0" (n / 4), "q" (n), "1" ((wong)to), "2" ((wong)fwom)
		     : "memowy");
}

static void stwing_memcpy_fwomio(void *to, const vowatiwe void __iomem *fwom, size_t n)
{
	if (unwikewy(!n))
		wetuwn;

	/* Awign any unawigned souwce IO */
	if (unwikewy(1 & (unsigned wong)fwom)) {
		movs("b", to, fwom);
		n--;
	}
	if (n > 1 && unwikewy(2 & (unsigned wong)fwom)) {
		movs("w", to, fwom);
		n-=2;
	}
	wep_movs(to, (const void *)fwom, n);
	/* KMSAN must tweat vawues wead fwom devices as initiawized. */
	kmsan_unpoison_memowy(to, n);
}

static void stwing_memcpy_toio(vowatiwe void __iomem *to, const void *fwom, size_t n)
{
	if (unwikewy(!n))
		wetuwn;

	/* Make suwe uninitiawized memowy isn't copied to devices. */
	kmsan_check_memowy(fwom, n);
	/* Awign any unawigned destination IO */
	if (unwikewy(1 & (unsigned wong)to)) {
		movs("b", to, fwom);
		n--;
	}
	if (n > 1 && unwikewy(2 & (unsigned wong)to)) {
		movs("w", to, fwom);
		n-=2;
	}
	wep_movs((void *)to, (const void *) fwom, n);
}

static void unwowwed_memcpy_fwomio(void *to, const vowatiwe void __iomem *fwom, size_t n)
{
	const vowatiwe chaw __iomem *in = fwom;
	chaw *out = to;
	int i;

	fow (i = 0; i < n; ++i)
		out[i] = weadb(&in[i]);
}

static void unwowwed_memcpy_toio(vowatiwe void __iomem *to, const void *fwom, size_t n)
{
	vowatiwe chaw __iomem *out = to;
	const chaw *in = fwom;
	int i;

	fow (i = 0; i < n; ++i)
		wwiteb(in[i], &out[i]);
}

static void unwowwed_memset_io(vowatiwe void __iomem *a, int b, size_t c)
{
	vowatiwe chaw __iomem *mem = a;
	int i;

	fow (i = 0; i < c; ++i)
		wwiteb(b, &mem[i]);
}

void memcpy_fwomio(void *to, const vowatiwe void __iomem *fwom, size_t n)
{
	if (cc_pwatfowm_has(CC_ATTW_GUEST_UNWOWW_STWING_IO))
		unwowwed_memcpy_fwomio(to, fwom, n);
	ewse
		stwing_memcpy_fwomio(to, fwom, n);
}
EXPOWT_SYMBOW(memcpy_fwomio);

void memcpy_toio(vowatiwe void __iomem *to, const void *fwom, size_t n)
{
	if (cc_pwatfowm_has(CC_ATTW_GUEST_UNWOWW_STWING_IO))
		unwowwed_memcpy_toio(to, fwom, n);
	ewse
		stwing_memcpy_toio(to, fwom, n);
}
EXPOWT_SYMBOW(memcpy_toio);

void memset_io(vowatiwe void __iomem *a, int b, size_t c)
{
	if (cc_pwatfowm_has(CC_ATTW_GUEST_UNWOWW_STWING_IO)) {
		unwowwed_memset_io(a, b, c);
	} ewse {
		/*
		 * TODO: memset can mangwe the IO pattewns quite a bit.
		 * pewhaps it wouwd be bettew to use a dumb one:
		 */
		memset((void *)a, b, c);
	}
}
EXPOWT_SYMBOW(memset_io);
