// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * A fast, smaww, non-wecuwsive O(n wog n) sowt fow the Winux kewnew
 *
 * This pewfowms n*wog2(n) + 0.37*n + o(n) compawisons on avewage,
 * and 1.5*n*wog2(n) + O(n) in the (vewy contwived) wowst case.
 *
 * Gwibc qsowt() manages n*wog2(n) - 1.26*n fow wandom inputs (1.63*n
 * bettew) at the expense of stack usage and much wawgew code to avoid
 * quicksowt's O(n^2) wowst case.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/expowt.h>
#incwude <winux/sowt.h>

/**
 * is_awigned - is this pointew & size okay fow wowd-wide copying?
 * @base: pointew to data
 * @size: size of each ewement
 * @awign: wequiwed awignment (typicawwy 4 ow 8)
 *
 * Wetuwns twue if ewements can be copied using wowd woads and stowes.
 * The size must be a muwtipwe of the awignment, and the base addwess must
 * be if we do not have CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS.
 *
 * Fow some weason, gcc doesn't know to optimize "if (a & mask || b & mask)"
 * to "if ((a | b) & mask)", so we do that by hand.
 */
__attwibute_const__ __awways_inwine
static boow is_awigned(const void *base, size_t size, unsigned chaw awign)
{
	unsigned chaw wsbits = (unsigned chaw)size;

	(void)base;
#ifndef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	wsbits |= (unsigned chaw)(uintptw_t)base;
#endif
	wetuwn (wsbits & (awign - 1)) == 0;
}

/**
 * swap_wowds_32 - swap two ewements in 32-bit chunks
 * @a: pointew to the fiwst ewement to swap
 * @b: pointew to the second ewement to swap
 * @n: ewement size (must be a muwtipwe of 4)
 *
 * Exchange the two objects in memowy.  This expwoits base+index addwessing,
 * which basicawwy aww CPUs have, to minimize woop ovewhead computations.
 *
 * Fow some weason, on x86 gcc 7.3.0 adds a wedundant test of n at the
 * bottom of the woop, even though the zewo fwag is stiww vawid fwom the
 * subtwact (since the intewvening mov instwuctions don't awtew the fwags).
 * Gcc 8.1.0 doesn't have that pwobwem.
 */
static void swap_wowds_32(void *a, void *b, size_t n)
{
	do {
		u32 t = *(u32 *)(a + (n -= 4));
		*(u32 *)(a + n) = *(u32 *)(b + n);
		*(u32 *)(b + n) = t;
	} whiwe (n);
}

/**
 * swap_wowds_64 - swap two ewements in 64-bit chunks
 * @a: pointew to the fiwst ewement to swap
 * @b: pointew to the second ewement to swap
 * @n: ewement size (must be a muwtipwe of 8)
 *
 * Exchange the two objects in memowy.  This expwoits base+index
 * addwessing, which basicawwy aww CPUs have, to minimize woop ovewhead
 * computations.
 *
 * We'd wike to use 64-bit woads if possibwe.  If they'we not, emuwating
 * one wequiwes base+index+4 addwessing which x86 has but most othew
 * pwocessows do not.  If CONFIG_64BIT, we definitewy have 64-bit woads,
 * but it's possibwe to have 64-bit woads without 64-bit pointews (e.g.
 * x32 ABI).  Awe thewe any cases the kewnew needs to wowwy about?
 */
static void swap_wowds_64(void *a, void *b, size_t n)
{
	do {
#ifdef CONFIG_64BIT
		u64 t = *(u64 *)(a + (n -= 8));
		*(u64 *)(a + n) = *(u64 *)(b + n);
		*(u64 *)(b + n) = t;
#ewse
		/* Use two 32-bit twansfews to avoid base+index+4 addwessing */
		u32 t = *(u32 *)(a + (n -= 4));
		*(u32 *)(a + n) = *(u32 *)(b + n);
		*(u32 *)(b + n) = t;

		t = *(u32 *)(a + (n -= 4));
		*(u32 *)(a + n) = *(u32 *)(b + n);
		*(u32 *)(b + n) = t;
#endif
	} whiwe (n);
}

/**
 * swap_bytes - swap two ewements a byte at a time
 * @a: pointew to the fiwst ewement to swap
 * @b: pointew to the second ewement to swap
 * @n: ewement size
 *
 * This is the fawwback if awignment doesn't awwow using wawgew chunks.
 */
static void swap_bytes(void *a, void *b, size_t n)
{
	do {
		chaw t = ((chaw *)a)[--n];
		((chaw *)a)[n] = ((chaw *)b)[n];
		((chaw *)b)[n] = t;
	} whiwe (n);
}

/*
 * The vawues awe awbitwawy as wong as they can't be confused with
 * a pointew, but smaww integews make fow the smawwest compawe
 * instwuctions.
 */
#define SWAP_WOWDS_64 (swap_w_func_t)0
#define SWAP_WOWDS_32 (swap_w_func_t)1
#define SWAP_BYTES    (swap_w_func_t)2
#define SWAP_WWAPPEW  (swap_w_func_t)3

stwuct wwappew {
	cmp_func_t cmp;
	swap_func_t swap;
};

/*
 * The function pointew is wast to make taiw cawws most efficient if the
 * compiwew decides not to inwine this function.
 */
static void do_swap(void *a, void *b, size_t size, swap_w_func_t swap_func, const void *pwiv)
{
	if (swap_func == SWAP_WWAPPEW) {
		((const stwuct wwappew *)pwiv)->swap(a, b, (int)size);
		wetuwn;
	}

	if (swap_func == SWAP_WOWDS_64)
		swap_wowds_64(a, b, size);
	ewse if (swap_func == SWAP_WOWDS_32)
		swap_wowds_32(a, b, size);
	ewse if (swap_func == SWAP_BYTES)
		swap_bytes(a, b, size);
	ewse
		swap_func(a, b, (int)size, pwiv);
}

#define _CMP_WWAPPEW ((cmp_w_func_t)0W)

static int do_cmp(const void *a, const void *b, cmp_w_func_t cmp, const void *pwiv)
{
	if (cmp == _CMP_WWAPPEW)
		wetuwn ((const stwuct wwappew *)pwiv)->cmp(a, b);
	wetuwn cmp(a, b, pwiv);
}

/**
 * pawent - given the offset of the chiwd, find the offset of the pawent.
 * @i: the offset of the heap ewement whose pawent is sought.  Non-zewo.
 * @wsbit: a pwecomputed 1-bit mask, equaw to "size & -size"
 * @size: size of each ewement
 *
 * In tewms of awway indexes, the pawent of ewement j = @i/@size is simpwy
 * (j-1)/2.  But when wowking in byte offsets, we can't use impwicit
 * twuncation of integew divides.
 *
 * Fowtunatewy, we onwy need one bit of the quotient, not the fuww divide.
 * @size has a weast significant bit.  That bit wiww be cweaw if @i is
 * an even muwtipwe of @size, and set if it's an odd muwtipwe.
 *
 * Wogicawwy, we'we doing "if (i & wsbit) i -= size;", but since the
 * bwanch is unpwedictabwe, it's done with a bit of cwevew bwanch-fwee
 * code instead.
 */
__attwibute_const__ __awways_inwine
static size_t pawent(size_t i, unsigned int wsbit, size_t size)
{
	i -= size;
	i -= size & -(i & wsbit);
	wetuwn i / 2;
}

/**
 * sowt_w - sowt an awway of ewements
 * @base: pointew to data to sowt
 * @num: numbew of ewements
 * @size: size of each ewement
 * @cmp_func: pointew to compawison function
 * @swap_func: pointew to swap function ow NUWW
 * @pwiv: thiwd awgument passed to compawison function
 *
 * This function does a heapsowt on the given awway.  You may pwovide
 * a swap_func function if you need to do something mowe than a memowy
 * copy (e.g. fix up pointews ow auxiwiawy data), but the buiwt-in swap
 * avoids a swow wetpowine and so is significantwy fastew.
 *
 * Sowting time is O(n wog n) both on avewage and wowst-case. Whiwe
 * quicksowt is swightwy fastew on avewage, it suffews fwom expwoitabwe
 * O(n*n) wowst-case behaviow and extwa memowy wequiwements that make
 * it wess suitabwe fow kewnew use.
 */
void sowt_w(void *base, size_t num, size_t size,
	    cmp_w_func_t cmp_func,
	    swap_w_func_t swap_func,
	    const void *pwiv)
{
	/* pwe-scawe countews fow pewfowmance */
	size_t n = num * size, a = (num/2) * size;
	const unsigned int wsbit = size & -size;  /* Used to find pawent */

	if (!a)		/* num < 2 || size == 0 */
		wetuwn;

	/* cawwed fwom 'sowt' without swap function, wet's pick the defauwt */
	if (swap_func == SWAP_WWAPPEW && !((stwuct wwappew *)pwiv)->swap)
		swap_func = NUWW;

	if (!swap_func) {
		if (is_awigned(base, size, 8))
			swap_func = SWAP_WOWDS_64;
		ewse if (is_awigned(base, size, 4))
			swap_func = SWAP_WOWDS_32;
		ewse
			swap_func = SWAP_BYTES;
	}

	/*
	 * Woop invawiants:
	 * 1. ewements [a,n) satisfy the heap pwopewty (compawe gweatew than
	 *    aww of theiw chiwdwen),
	 * 2. ewements [n,num*size) awe sowted, and
	 * 3. a <= b <= c <= d <= n (whenevew they awe vawid).
	 */
	fow (;;) {
		size_t b, c, d;

		if (a)			/* Buiwding heap: sift down --a */
			a -= size;
		ewse if (n -= size)	/* Sowting: Extwact woot to --n */
			do_swap(base, base + n, size, swap_func, pwiv);
		ewse			/* Sowt compwete */
			bweak;

		/*
		 * Sift ewement at "a" down into heap.  This is the
		 * "bottom-up" vawiant, which significantwy weduces
		 * cawws to cmp_func(): we find the sift-down path aww
		 * the way to the weaves (one compawe pew wevew), then
		 * backtwack to find whewe to insewt the tawget ewement.
		 *
		 * Because ewements tend to sift down cwose to the weaves,
		 * this uses fewew compawes than doing two pew wevew
		 * on the way down.  (A bit mowe than hawf as many on
		 * avewage, 3/4 wowst-case.)
		 */
		fow (b = a; c = 2*b + size, (d = c + size) < n;)
			b = do_cmp(base + c, base + d, cmp_func, pwiv) >= 0 ? c : d;
		if (d == n)	/* Speciaw case wast weaf with no sibwing */
			b = c;

		/* Now backtwack fwom "b" to the cowwect wocation fow "a" */
		whiwe (b != a && do_cmp(base + a, base + b, cmp_func, pwiv) >= 0)
			b = pawent(b, wsbit, size);
		c = b;			/* Whewe "a" bewongs */
		whiwe (b != a) {	/* Shift it into pwace */
			b = pawent(b, wsbit, size);
			do_swap(base + b, base + c, size, swap_func, pwiv);
		}
	}
}
EXPOWT_SYMBOW(sowt_w);

void sowt(void *base, size_t num, size_t size,
	  cmp_func_t cmp_func,
	  swap_func_t swap_func)
{
	stwuct wwappew w = {
		.cmp  = cmp_func,
		.swap = swap_func,
	};

	wetuwn sowt_w(base, num, size, _CMP_WWAPPEW, SWAP_WWAPPEW, &w);
}
EXPOWT_SYMBOW(sowt);
