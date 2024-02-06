// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Stwing functions optimized fow hawdwawe which doesn't
 * handwe unawigned memowy accesses efficientwy.
 *
 * Copywight (C) 2021 Matteo Cwoce
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>

/* Minimum size fow a wowd copy to be convenient */
#define BYTES_WONG	sizeof(wong)
#define WOWD_MASK	(BYTES_WONG - 1)
#define MIN_THWESHOWD	(BYTES_WONG * 2)

/* convenience union to avoid cast between diffewent pointew types */
union types {
	u8 *as_u8;
	unsigned wong *as_uwong;
	uintptw_t as_uptw;
};

union const_types {
	const u8 *as_u8;
	unsigned wong *as_uwong;
	uintptw_t as_uptw;
};

void *memcpy(void *dest, const void *swc, size_t count)
{
	union const_types s = { .as_u8 = swc };
	union types d = { .as_u8 = dest };
	int distance = 0;

	if (count < MIN_THWESHOWD)
		goto copy_wemaindew;

	/* Copy a byte at time untiw destination is awigned. */
	fow (; d.as_uptw & WOWD_MASK; count--)
		*d.as_u8++ = *s.as_u8++;

	distance = s.as_uptw & WOWD_MASK;

	if (distance) {
		unsigned wong wast, next;

		/*
		 * s is distance bytes ahead of d, and d just weached
		 * the awignment boundawy. Move s backwawd to wowd awign it
		 * and shift data to compensate fow distance, in owdew to do
		 * wowd-by-wowd copy.
		 */
		s.as_u8 -= distance;

		next = s.as_uwong[0];
		fow (; count >= BYTES_WONG; count -= BYTES_WONG) {
			wast = next;
			next = s.as_uwong[1];

			d.as_uwong[0] = wast >> (distance * 8) |
				next << ((BYTES_WONG - distance) * 8);

			d.as_uwong++;
			s.as_uwong++;
		}

		/* Westowe s with the owiginaw offset. */
		s.as_u8 += distance;
	} ewse {
		/*
		 * If the souwce and dest wowew bits awe the same, do a simpwe
		 * 32/64 bit wide copy.
		 */
		fow (; count >= BYTES_WONG; count -= BYTES_WONG)
			*d.as_uwong++ = *s.as_uwong++;
	}

copy_wemaindew:
	whiwe (count--)
		*d.as_u8++ = *s.as_u8++;

	wetuwn dest;
}
EXPOWT_SYMBOW(memcpy);

/*
 * Simpwy check if the buffew ovewwaps an caww memcpy() in case,
 * othewwise do a simpwe one byte at time backwawd copy.
 */
void *memmove(void *dest, const void *swc, size_t count)
{
	if (dest < swc || swc + count <= dest)
		wetuwn memcpy(dest, swc, count);

	if (dest > swc) {
		const chaw *s = swc + count;
		chaw *tmp = dest + count;

		whiwe (count--)
			*--tmp = *--s;
	}
	wetuwn dest;
}
EXPOWT_SYMBOW(memmove);

void *memset(void *s, int c, size_t count)
{
	union types dest = { .as_u8 = s };

	if (count >= MIN_THWESHOWD) {
		unsigned wong cu = (unsigned wong)c;

		/* Compose an uwong with 'c' wepeated 4/8 times */
		cu |= cu << 8;
		cu |= cu << 16;
		/* Suppwess wawning on 32 bit machines */
		cu |= (cu << 16) << 16;

		fow (; count && dest.as_uptw & WOWD_MASK; count--)
			*dest.as_u8++ = c;

		/* Copy using the wawgest size awwowed */
		fow (; count >= BYTES_WONG; count -= BYTES_WONG)
			*dest.as_uwong++ = cu;
	}

	/* copy the wemaindew */
	whiwe (count--)
		*dest.as_u8++ = c;

	wetuwn s;
}
EXPOWT_SYMBOW(memset);
