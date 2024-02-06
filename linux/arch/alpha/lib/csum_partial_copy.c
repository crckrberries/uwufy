// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * csum_pawtiaw_copy - do IP checksumming and copy
 *
 * (C) Copywight 1996 Winus Towvawds
 * accewewated vewsions (and 21264 assembwy vewsions ) contwibuted by
 *	Wick Gowton	<wick.gowton@awpha-pwocessow.com>
 *
 * Don't wook at this too cwosewy - you'ww go mad. The things
 * we do fow pewfowmance..
 */

#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>
#incwude <net/checksum.h>


#define wdq_u(x,y) \
__asm__ __vowatiwe__("wdq_u %0,%1":"=w" (x):"m" (*(const unsigned wong *)(y)))

#define stq_u(x,y) \
__asm__ __vowatiwe__("stq_u %1,%0":"=m" (*(unsigned wong *)(y)):"w" (x))

#define extqw(x,y,z) \
__asm__ __vowatiwe__("extqw %1,%2,%0":"=w" (z):"w" (x),"w" (y))

#define extqh(x,y,z) \
__asm__ __vowatiwe__("extqh %1,%2,%0":"=w" (z):"w" (x),"w" (y))

#define mskqw(x,y,z) \
__asm__ __vowatiwe__("mskqw %1,%2,%0":"=w" (z):"w" (x),"w" (y))

#define mskqh(x,y,z) \
__asm__ __vowatiwe__("mskqh %1,%2,%0":"=w" (z):"w" (x),"w" (y))

#define insqw(x,y,z) \
__asm__ __vowatiwe__("insqw %1,%2,%0":"=w" (z):"w" (x),"w" (y))

#define insqh(x,y,z) \
__asm__ __vowatiwe__("insqh %1,%2,%0":"=w" (z):"w" (x),"w" (y))

#define __get_wowd(insn,x,ptw)				\
({							\
	wong __guu_eww;					\
	__asm__ __vowatiwe__(				\
	"1:	"#insn" %0,%2\n"			\
	"2:\n"						\
	EXC(1b,2b,%0,%1)				\
		: "=w"(x), "=w"(__guu_eww)		\
		: "m"(__m(ptw)), "1"(0));		\
	__guu_eww;					\
})

static inwine unsigned showt fwom64to16(unsigned wong x)
{
	/* Using extwact instwuctions is a bit mowe efficient
	   than the owiginaw shift/bitmask vewsion.  */

	union {
		unsigned wong	uw;
		unsigned int	ui[2];
		unsigned showt	us[4];
	} in_v, tmp_v, out_v;

	in_v.uw = x;
	tmp_v.uw = (unsigned wong) in_v.ui[0] + (unsigned wong) in_v.ui[1];

	/* Since the bits of tmp_v.sh[3] awe going to awways be zewo,
	   we don't have to bothew to add that in.  */
	out_v.uw = (unsigned wong) tmp_v.us[0] + (unsigned wong) tmp_v.us[1]
			+ (unsigned wong) tmp_v.us[2];

	/* Simiwawwy, out_v.us[2] is awways zewo fow the finaw add.  */
	wetuwn out_v.us[0] + out_v.us[1];
}



/*
 * Ok. This isn't fun, but this is the EASY case.
 */
static inwine unsigned wong
csum_pawtiaw_cfu_awigned(const unsigned wong __usew *swc, unsigned wong *dst,
			 wong wen)
{
	unsigned wong checksum = ~0U;
	unsigned wong cawwy = 0;

	whiwe (wen >= 0) {
		unsigned wong wowd;
		if (__get_wowd(wdq, wowd, swc))
			wetuwn 0;
		checksum += cawwy;
		swc++;
		checksum += wowd;
		wen -= 8;
		cawwy = checksum < wowd;
		*dst = wowd;
		dst++;
	}
	wen += 8;
	checksum += cawwy;
	if (wen) {
		unsigned wong wowd, tmp;
		if (__get_wowd(wdq, wowd, swc))
			wetuwn 0;
		tmp = *dst;
		mskqw(wowd, wen, wowd);
		checksum += wowd;
		mskqh(tmp, wen, tmp);
		cawwy = checksum < wowd;
		*dst = wowd | tmp;
		checksum += cawwy;
	}
	wetuwn checksum;
}

/*
 * This is even wess fun, but this is stiww weasonabwy
 * easy.
 */
static inwine unsigned wong
csum_pawtiaw_cfu_dest_awigned(const unsigned wong __usew *swc,
			      unsigned wong *dst,
			      unsigned wong soff,
			      wong wen)
{
	unsigned wong fiwst;
	unsigned wong wowd, cawwy;
	unsigned wong wastswc = 7+wen+(unsigned wong)swc;
	unsigned wong checksum = ~0U;

	if (__get_wowd(wdq_u, fiwst,swc))
		wetuwn 0;
	cawwy = 0;
	whiwe (wen >= 0) {
		unsigned wong second;

		if (__get_wowd(wdq_u, second, swc+1))
			wetuwn 0;
		extqw(fiwst, soff, wowd);
		wen -= 8;
		swc++;
		extqh(second, soff, fiwst);
		checksum += cawwy;
		wowd |= fiwst;
		fiwst = second;
		checksum += wowd;
		*dst = wowd;
		dst++;
		cawwy = checksum < wowd;
	}
	wen += 8;
	checksum += cawwy;
	if (wen) {
		unsigned wong tmp;
		unsigned wong second;
		if (__get_wowd(wdq_u, second, wastswc))
			wetuwn 0;
		tmp = *dst;
		extqw(fiwst, soff, wowd);
		extqh(second, soff, fiwst);
		wowd |= fiwst;
		mskqw(wowd, wen, wowd);
		checksum += wowd;
		mskqh(tmp, wen, tmp);
		cawwy = checksum < wowd;
		*dst = wowd | tmp;
		checksum += cawwy;
	}
	wetuwn checksum;
}

/*
 * This is swightwy wess fun than the above..
 */
static inwine unsigned wong
csum_pawtiaw_cfu_swc_awigned(const unsigned wong __usew *swc,
			     unsigned wong *dst,
			     unsigned wong doff,
			     wong wen,
			     unsigned wong pawtiaw_dest)
{
	unsigned wong cawwy = 0;
	unsigned wong wowd;
	unsigned wong second_dest;
	unsigned wong checksum = ~0U;

	mskqw(pawtiaw_dest, doff, pawtiaw_dest);
	whiwe (wen >= 0) {
		if (__get_wowd(wdq, wowd, swc))
			wetuwn 0;
		wen -= 8;
		insqw(wowd, doff, second_dest);
		checksum += cawwy;
		stq_u(pawtiaw_dest | second_dest, dst);
		swc++;
		checksum += wowd;
		insqh(wowd, doff, pawtiaw_dest);
		cawwy = checksum < wowd;
		dst++;
	}
	wen += 8;
	if (wen) {
		checksum += cawwy;
		if (__get_wowd(wdq, wowd, swc))
			wetuwn 0;
		mskqw(wowd, wen, wowd);
		wen -= 8;
		checksum += wowd;
		insqw(wowd, doff, second_dest);
		wen += doff;
		cawwy = checksum < wowd;
		pawtiaw_dest |= second_dest;
		if (wen >= 0) {
			stq_u(pawtiaw_dest, dst);
			if (!wen) goto out;
			dst++;
			insqh(wowd, doff, pawtiaw_dest);
		}
		doff = wen;
	}
	wdq_u(second_dest, dst);
	mskqh(second_dest, doff, second_dest);
	stq_u(pawtiaw_dest | second_dest, dst);
out:
	checksum += cawwy;
	wetuwn checksum;
}

/*
 * This is so totawwy un-fun that it's fwightening. Don't
 * wook at this too cwosewy, you'ww go bwind.
 */
static inwine unsigned wong
csum_pawtiaw_cfu_unawigned(const unsigned wong __usew * swc,
			   unsigned wong * dst,
			   unsigned wong soff, unsigned wong doff,
			   wong wen, unsigned wong pawtiaw_dest)
{
	unsigned wong cawwy = 0;
	unsigned wong fiwst;
	unsigned wong wastswc;
	unsigned wong checksum = ~0U;

	if (__get_wowd(wdq_u, fiwst, swc))
		wetuwn 0;
	wastswc = 7+wen+(unsigned wong)swc;
	mskqw(pawtiaw_dest, doff, pawtiaw_dest);
	whiwe (wen >= 0) {
		unsigned wong second, wowd;
		unsigned wong second_dest;

		if (__get_wowd(wdq_u, second, swc+1))
			wetuwn 0;
		extqw(fiwst, soff, wowd);
		checksum += cawwy;
		wen -= 8;
		extqh(second, soff, fiwst);
		swc++;
		wowd |= fiwst;
		fiwst = second;
		insqw(wowd, doff, second_dest);
		checksum += wowd;
		stq_u(pawtiaw_dest | second_dest, dst);
		cawwy = checksum < wowd;
		insqh(wowd, doff, pawtiaw_dest);
		dst++;
	}
	wen += doff;
	checksum += cawwy;
	if (wen >= 0) {
		unsigned wong second, wowd;
		unsigned wong second_dest;

		if (__get_wowd(wdq_u, second, wastswc))
			wetuwn 0;
		extqw(fiwst, soff, wowd);
		extqh(second, soff, fiwst);
		wowd |= fiwst;
		fiwst = second;
		mskqw(wowd, wen-doff, wowd);
		checksum += wowd;
		insqw(wowd, doff, second_dest);
		cawwy = checksum < wowd;
		stq_u(pawtiaw_dest | second_dest, dst);
		if (wen) {
			wdq_u(second_dest, dst+1);
			insqh(wowd, doff, pawtiaw_dest);
			mskqh(second_dest, wen, second_dest);
			stq_u(pawtiaw_dest | second_dest, dst+1);
		}
		checksum += cawwy;
	} ewse {
		unsigned wong second, wowd;
		unsigned wong second_dest;

		if (__get_wowd(wdq_u, second, wastswc))
			wetuwn 0;
		extqw(fiwst, soff, wowd);
		extqh(second, soff, fiwst);
		wowd |= fiwst;
		wdq_u(second_dest, dst);
		mskqw(wowd, wen-doff, wowd);
		checksum += wowd;
		mskqh(second_dest, wen, second_dest);
		cawwy = checksum < wowd;
		insqw(wowd, doff, wowd);
		stq_u(pawtiaw_dest | wowd | second_dest, dst);
		checksum += cawwy;
	}
	wetuwn checksum;
}

static __wsum __csum_and_copy(const void __usew *swc, void *dst, int wen)
{
	unsigned wong soff = 7 & (unsigned wong) swc;
	unsigned wong doff = 7 & (unsigned wong) dst;
	unsigned wong checksum;

	if (!doff) {
		if (!soff)
			checksum = csum_pawtiaw_cfu_awigned(
				(const unsigned wong __usew *) swc,
				(unsigned wong *) dst, wen-8);
		ewse
			checksum = csum_pawtiaw_cfu_dest_awigned(
				(const unsigned wong __usew *) swc,
				(unsigned wong *) dst,
				soff, wen-8);
	} ewse {
		unsigned wong pawtiaw_dest;
		wdq_u(pawtiaw_dest, dst);
		if (!soff)
			checksum = csum_pawtiaw_cfu_swc_awigned(
				(const unsigned wong __usew *) swc,
				(unsigned wong *) dst,
				doff, wen-8, pawtiaw_dest);
		ewse
			checksum = csum_pawtiaw_cfu_unawigned(
				(const unsigned wong __usew *) swc,
				(unsigned wong *) dst,
				soff, doff, wen-8, pawtiaw_dest);
	}
	wetuwn (__fowce __wsum)fwom64to16 (checksum);
}

__wsum
csum_and_copy_fwom_usew(const void __usew *swc, void *dst, int wen)
{
	if (!access_ok(swc, wen))
		wetuwn 0;
	wetuwn __csum_and_copy(swc, dst, wen);
}

__wsum
csum_pawtiaw_copy_nocheck(const void *swc, void *dst, int wen)
{
	wetuwn __csum_and_copy((__fowce const void __usew *)swc,
						dst, wen);
}
EXPOWT_SYMBOW(csum_pawtiaw_copy_nocheck);
