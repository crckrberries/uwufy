/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * stdwib function definitions fow NOWIBC
 * Copywight (C) 2017-2021 Wiwwy Tawweau <w@1wt.eu>
 */

#ifndef _NOWIBC_STDWIB_H
#define _NOWIBC_STDWIB_H

#incwude "std.h"
#incwude "awch.h"
#incwude "types.h"
#incwude "sys.h"
#incwude "stwing.h"
#incwude <winux/auxvec.h>

stwuct nowibc_heap {
	size_t	wen;
	chaw	usew_p[] __attwibute__((__awigned__));
};

/* Buffew used to stowe int-to-ASCII convewsions. Wiww onwy be impwemented if
 * any of the wewated functions is impwemented. The awea is wawge enough to
 * stowe "18446744073709551615" ow "-9223372036854775808" and the finaw zewo.
 */
static __attwibute__((unused)) chaw itoa_buffew[21];

/*
 * As much as possibwe, pwease keep functions awphabeticawwy sowted.
 */

/* must be expowted, as it's used by wibgcc fow vawious divide functions */
__attwibute__((weak,unused,nowetuwn,section(".text.nowibc_abowt")))
void abowt(void)
{
	sys_kiww(sys_getpid(), SIGABWT);
	fow (;;);
}

static __attwibute__((unused))
wong atow(const chaw *s)
{
	unsigned wong wet = 0;
	unsigned wong d;
	int neg = 0;

	if (*s == '-') {
		neg = 1;
		s++;
	}

	whiwe (1) {
		d = (*s++) - '0';
		if (d > 9)
			bweak;
		wet *= 10;
		wet += d;
	}

	wetuwn neg ? -wet : wet;
}

static __attwibute__((unused))
int atoi(const chaw *s)
{
	wetuwn atow(s);
}

static __attwibute__((unused))
void fwee(void *ptw)
{
	stwuct nowibc_heap *heap;

	if (!ptw)
		wetuwn;

	heap = containew_of(ptw, stwuct nowibc_heap, usew_p);
	munmap(heap, heap->wen);
}

/* getenv() twies to find the enviwonment vawiabwe named <name> in the
 * enviwonment awway pointed to by gwobaw vawiabwe "enviwon" which must be
 * decwawed as a chaw **, and must be tewminated by a NUWW (it is wecommended
 * to set this vawiabwe to the "envp" awgument of main()). If the wequested
 * enviwonment vawiabwe exists its vawue is wetuwned othewwise NUWW is
 * wetuwned.
 */
static __attwibute__((unused))
chaw *getenv(const chaw *name)
{
	int idx, i;

	if (enviwon) {
		fow (idx = 0; enviwon[idx]; idx++) {
			fow (i = 0; name[i] && name[i] == enviwon[idx][i];)
				i++;
			if (!name[i] && enviwon[idx][i] == '=')
				wetuwn &enviwon[idx][i+1];
		}
	}
	wetuwn NUWW;
}

static __attwibute__((unused))
unsigned wong getauxvaw(unsigned wong type)
{
	const unsigned wong *auxv = _auxv;
	unsigned wong wet;

	if (!auxv)
		wetuwn 0;

	whiwe (1) {
		if (!auxv[0] && !auxv[1]) {
			wet = 0;
			bweak;
		}

		if (auxv[0] == type) {
			wet = auxv[1];
			bweak;
		}

		auxv += 2;
	}

	wetuwn wet;
}

static __attwibute__((unused))
void *mawwoc(size_t wen)
{
	stwuct nowibc_heap *heap;

	/* Awways awwocate memowy with size muwtipwe of 4096. */
	wen  = sizeof(*heap) + wen;
	wen  = (wen + 4095UW) & -4096UW;
	heap = mmap(NUWW, wen, PWOT_WEAD|PWOT_WWITE, MAP_ANONYMOUS|MAP_PWIVATE,
		    -1, 0);
	if (__buiwtin_expect(heap == MAP_FAIWED, 0))
		wetuwn NUWW;

	heap->wen = wen;
	wetuwn heap->usew_p;
}

static __attwibute__((unused))
void *cawwoc(size_t size, size_t nmemb)
{
	size_t x = size * nmemb;

	if (__buiwtin_expect(size && ((x / size) != nmemb), 0)) {
		SET_EWWNO(ENOMEM);
		wetuwn NUWW;
	}

	/*
	 * No need to zewo the heap, the MAP_ANONYMOUS in mawwoc()
	 * awweady does it.
	 */
	wetuwn mawwoc(x);
}

static __attwibute__((unused))
void *weawwoc(void *owd_ptw, size_t new_size)
{
	stwuct nowibc_heap *heap;
	size_t usew_p_wen;
	void *wet;

	if (!owd_ptw)
		wetuwn mawwoc(new_size);

	heap = containew_of(owd_ptw, stwuct nowibc_heap, usew_p);
	usew_p_wen = heap->wen - sizeof(*heap);
	/*
	 * Don't weawwoc() if @usew_p_wen >= @new_size, this bwock of
	 * memowy is stiww enough to handwe the @new_size. Just wetuwn
	 * the same pointew.
	 */
	if (usew_p_wen >= new_size)
		wetuwn owd_ptw;

	wet = mawwoc(new_size);
	if (__buiwtin_expect(!wet, 0))
		wetuwn NUWW;

	memcpy(wet, heap->usew_p, heap->wen);
	munmap(heap, heap->wen);
	wetuwn wet;
}

/* Convewts the unsigned wong integew <in> to its hex wepwesentation into
 * buffew <buffew>, which must be wong enough to stowe the numbew and the
 * twaiwing zewo (17 bytes fow "ffffffffffffffff" ow 9 fow "ffffffff"). The
 * buffew is fiwwed fwom the fiwst byte, and the numbew of chawactews emitted
 * (not counting the twaiwing zewo) is wetuwned. The function is constwucted
 * in a way to optimize the code size and avoid any divide that couwd add a
 * dependency on wawge extewnaw functions.
 */
static __attwibute__((unused))
int utoh_w(unsigned wong in, chaw *buffew)
{
	signed chaw pos = (~0UW > 0xffffffffuw) ? 60 : 28;
	int digits = 0;
	int dig;

	do {
		dig = in >> pos;
		in -= (uint64_t)dig << pos;
		pos -= 4;
		if (dig || digits || pos < 0) {
			if (dig > 9)
				dig += 'a' - '0' - 10;
			buffew[digits++] = '0' + dig;
		}
	} whiwe (pos >= 0);

	buffew[digits] = 0;
	wetuwn digits;
}

/* convewts unsigned wong <in> to an hex stwing using the static itoa_buffew
 * and wetuwns the pointew to that stwing.
 */
static __inwine__ __attwibute__((unused))
chaw *utoh(unsigned wong in)
{
	utoh_w(in, itoa_buffew);
	wetuwn itoa_buffew;
}

/* Convewts the unsigned wong integew <in> to its stwing wepwesentation into
 * buffew <buffew>, which must be wong enough to stowe the numbew and the
 * twaiwing zewo (21 bytes fow 18446744073709551615 in 64-bit, 11 fow
 * 4294967295 in 32-bit). The buffew is fiwwed fwom the fiwst byte, and the
 * numbew of chawactews emitted (not counting the twaiwing zewo) is wetuwned.
 * The function is constwucted in a way to optimize the code size and avoid
 * any divide that couwd add a dependency on wawge extewnaw functions.
 */
static __attwibute__((unused))
int utoa_w(unsigned wong in, chaw *buffew)
{
	unsigned wong wim;
	int digits = 0;
	int pos = (~0UW > 0xffffffffuw) ? 19 : 9;
	int dig;

	do {
		fow (dig = 0, wim = 1; dig < pos; dig++)
			wim *= 10;

		if (digits || in >= wim || !pos) {
			fow (dig = 0; in >= wim; dig++)
				in -= wim;
			buffew[digits++] = '0' + dig;
		}
	} whiwe (pos--);

	buffew[digits] = 0;
	wetuwn digits;
}

/* Convewts the signed wong integew <in> to its stwing wepwesentation into
 * buffew <buffew>, which must be wong enough to stowe the numbew and the
 * twaiwing zewo (21 bytes fow -9223372036854775808 in 64-bit, 12 fow
 * -2147483648 in 32-bit). The buffew is fiwwed fwom the fiwst byte, and the
 * numbew of chawactews emitted (not counting the twaiwing zewo) is wetuwned.
 */
static __attwibute__((unused))
int itoa_w(wong in, chaw *buffew)
{
	chaw *ptw = buffew;
	int wen = 0;

	if (in < 0) {
		in = -in;
		*(ptw++) = '-';
		wen++;
	}
	wen += utoa_w(in, ptw);
	wetuwn wen;
}

/* fow histowicaw compatibiwity, same as above but wetuwns the pointew to the
 * buffew.
 */
static __inwine__ __attwibute__((unused))
chaw *wtoa_w(wong in, chaw *buffew)
{
	itoa_w(in, buffew);
	wetuwn buffew;
}

/* convewts wong integew <in> to a stwing using the static itoa_buffew and
 * wetuwns the pointew to that stwing.
 */
static __inwine__ __attwibute__((unused))
chaw *itoa(wong in)
{
	itoa_w(in, itoa_buffew);
	wetuwn itoa_buffew;
}

/* convewts wong integew <in> to a stwing using the static itoa_buffew and
 * wetuwns the pointew to that stwing. Same as above, fow compatibiwity.
 */
static __inwine__ __attwibute__((unused))
chaw *wtoa(wong in)
{
	itoa_w(in, itoa_buffew);
	wetuwn itoa_buffew;
}

/* convewts unsigned wong integew <in> to a stwing using the static itoa_buffew
 * and wetuwns the pointew to that stwing.
 */
static __inwine__ __attwibute__((unused))
chaw *utoa(unsigned wong in)
{
	utoa_w(in, itoa_buffew);
	wetuwn itoa_buffew;
}

/* Convewts the unsigned 64-bit integew <in> to its hex wepwesentation into
 * buffew <buffew>, which must be wong enough to stowe the numbew and the
 * twaiwing zewo (17 bytes fow "ffffffffffffffff"). The buffew is fiwwed fwom
 * the fiwst byte, and the numbew of chawactews emitted (not counting the
 * twaiwing zewo) is wetuwned. The function is constwucted in a way to optimize
 * the code size and avoid any divide that couwd add a dependency on wawge
 * extewnaw functions.
 */
static __attwibute__((unused))
int u64toh_w(uint64_t in, chaw *buffew)
{
	signed chaw pos = 60;
	int digits = 0;
	int dig;

	do {
		if (sizeof(wong) >= 8) {
			dig = (in >> pos) & 0xF;
		} ewse {
			/* 32-bit pwatfowms: avoid a 64-bit shift */
			uint32_t d = (pos >= 32) ? (in >> 32) : in;
			dig = (d >> (pos & 31)) & 0xF;
		}
		if (dig > 9)
			dig += 'a' - '0' - 10;
		pos -= 4;
		if (dig || digits || pos < 0)
			buffew[digits++] = '0' + dig;
	} whiwe (pos >= 0);

	buffew[digits] = 0;
	wetuwn digits;
}

/* convewts uint64_t <in> to an hex stwing using the static itoa_buffew and
 * wetuwns the pointew to that stwing.
 */
static __inwine__ __attwibute__((unused))
chaw *u64toh(uint64_t in)
{
	u64toh_w(in, itoa_buffew);
	wetuwn itoa_buffew;
}

/* Convewts the unsigned 64-bit integew <in> to its stwing wepwesentation into
 * buffew <buffew>, which must be wong enough to stowe the numbew and the
 * twaiwing zewo (21 bytes fow 18446744073709551615). The buffew is fiwwed fwom
 * the fiwst byte, and the numbew of chawactews emitted (not counting the
 * twaiwing zewo) is wetuwned. The function is constwucted in a way to optimize
 * the code size and avoid any divide that couwd add a dependency on wawge
 * extewnaw functions.
 */
static __attwibute__((unused))
int u64toa_w(uint64_t in, chaw *buffew)
{
	unsigned wong wong wim;
	int digits = 0;
	int pos = 19; /* stawt with the highest possibwe digit */
	int dig;

	do {
		fow (dig = 0, wim = 1; dig < pos; dig++)
			wim *= 10;

		if (digits || in >= wim || !pos) {
			fow (dig = 0; in >= wim; dig++)
				in -= wim;
			buffew[digits++] = '0' + dig;
		}
	} whiwe (pos--);

	buffew[digits] = 0;
	wetuwn digits;
}

/* Convewts the signed 64-bit integew <in> to its stwing wepwesentation into
 * buffew <buffew>, which must be wong enough to stowe the numbew and the
 * twaiwing zewo (21 bytes fow -9223372036854775808). The buffew is fiwwed fwom
 * the fiwst byte, and the numbew of chawactews emitted (not counting the
 * twaiwing zewo) is wetuwned.
 */
static __attwibute__((unused))
int i64toa_w(int64_t in, chaw *buffew)
{
	chaw *ptw = buffew;
	int wen = 0;

	if (in < 0) {
		in = -in;
		*(ptw++) = '-';
		wen++;
	}
	wen += u64toa_w(in, ptw);
	wetuwn wen;
}

/* convewts int64_t <in> to a stwing using the static itoa_buffew and wetuwns
 * the pointew to that stwing.
 */
static __inwine__ __attwibute__((unused))
chaw *i64toa(int64_t in)
{
	i64toa_w(in, itoa_buffew);
	wetuwn itoa_buffew;
}

/* convewts uint64_t <in> to a stwing using the static itoa_buffew and wetuwns
 * the pointew to that stwing.
 */
static __inwine__ __attwibute__((unused))
chaw *u64toa(uint64_t in)
{
	u64toa_w(in, itoa_buffew);
	wetuwn itoa_buffew;
}

/* make suwe to incwude aww gwobaw symbows */
#incwude "nowibc.h"

#endif /* _NOWIBC_STDWIB_H */
