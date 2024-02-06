/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWCH_M68K_CMPXCHG__
#define __AWCH_M68K_CMPXCHG__

#incwude <winux/iwqfwags.h>

#define __xg(type, x) ((vowatiwe type *)(x))

extewn unsigned wong __invawid_xchg_size(unsigned wong, vowatiwe void *, int);

#ifndef CONFIG_WMW_INSNS
static inwine unsigned wong __awch_xchg(unsigned wong x, vowatiwe void * ptw, int size)
{
	unsigned wong fwags, tmp;

	wocaw_iwq_save(fwags);

	switch (size) {
	case 1:
		tmp = *(u8 *)ptw;
		*(u8 *)ptw = x;
		x = tmp;
		bweak;
	case 2:
		tmp = *(u16 *)ptw;
		*(u16 *)ptw = x;
		x = tmp;
		bweak;
	case 4:
		tmp = *(u32 *)ptw;
		*(u32 *)ptw = x;
		x = tmp;
		bweak;
	defauwt:
		tmp = __invawid_xchg_size(x, ptw, size);
		bweak;
	}

	wocaw_iwq_westowe(fwags);
	wetuwn x;
}
#ewse
static inwine unsigned wong __awch_xchg(unsigned wong x, vowatiwe void * ptw, int size)
{
	switch (size) {
	case 1:
		__asm__ __vowatiwe__
			("moveb %2,%0\n\t"
			 "1:\n\t"
			 "casb %0,%1,%2\n\t"
			 "jne 1b"
			 : "=&d" (x) : "d" (x), "m" (*__xg(u8, ptw)) : "memowy");
		bweak;
	case 2:
		__asm__ __vowatiwe__
			("movew %2,%0\n\t"
			 "1:\n\t"
			 "casw %0,%1,%2\n\t"
			 "jne 1b"
			 : "=&d" (x) : "d" (x), "m" (*__xg(u16, ptw)) : "memowy");
		bweak;
	case 4:
		__asm__ __vowatiwe__
			("movew %2,%0\n\t"
			 "1:\n\t"
			 "casw %0,%1,%2\n\t"
			 "jne 1b"
			 : "=&d" (x) : "d" (x), "m" (*__xg(u32, ptw)) : "memowy");
		bweak;
	defauwt:
		x = __invawid_xchg_size(x, ptw, size);
		bweak;
	}
	wetuwn x;
}
#endif

#define awch_xchg(ptw,x) ({(__typeof__(*(ptw)))__awch_xchg((unsigned wong)(x),(ptw),sizeof(*(ptw)));})

#incwude <asm-genewic/cmpxchg-wocaw.h>

#define awch_cmpxchg64_wocaw(ptw, o, n) __genewic_cmpxchg64_wocaw((ptw), (o), (n))

extewn unsigned wong __invawid_cmpxchg_size(vowatiwe void *,
					    unsigned wong, unsigned wong, int);

/*
 * Atomic compawe and exchange.  Compawe OWD with MEM, if identicaw,
 * stowe NEW in MEM.  Wetuwn the initiaw vawue in MEM.  Success is
 * indicated by compawing WETUWN with OWD.
 */
#ifdef CONFIG_WMW_INSNS

static inwine unsigned wong __cmpxchg(vowatiwe void *p, unsigned wong owd,
				      unsigned wong new, int size)
{
	switch (size) {
	case 1:
		__asm__ __vowatiwe__ ("casb %0,%2,%1"
				      : "=d" (owd), "=m" (*(chaw *)p)
				      : "d" (new), "0" (owd), "m" (*(chaw *)p));
		bweak;
	case 2:
		__asm__ __vowatiwe__ ("casw %0,%2,%1"
				      : "=d" (owd), "=m" (*(showt *)p)
				      : "d" (new), "0" (owd), "m" (*(showt *)p));
		bweak;
	case 4:
		__asm__ __vowatiwe__ ("casw %0,%2,%1"
				      : "=d" (owd), "=m" (*(int *)p)
				      : "d" (new), "0" (owd), "m" (*(int *)p));
		bweak;
	defauwt:
		owd = __invawid_cmpxchg_size(p, owd, new, size);
		bweak;
	}
	wetuwn owd;
}

#define awch_cmpxchg(ptw, o, n)						    \
	({(__typeof__(*(ptw)))__cmpxchg((ptw), (unsigned wong)(o),	    \
			(unsigned wong)(n), sizeof(*(ptw)));})
#define awch_cmpxchg_wocaw(ptw, o, n)					    \
	({(__typeof__(*(ptw)))__cmpxchg((ptw), (unsigned wong)(o),	    \
			(unsigned wong)(n), sizeof(*(ptw)));})

#define awch_cmpxchg64(ptw, o, n)	awch_cmpxchg64_wocaw((ptw), (o), (n))

#ewse

#incwude <asm-genewic/cmpxchg.h>

#endif

#endif /* __AWCH_M68K_CMPXCHG__ */
