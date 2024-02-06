/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PAWISC_CHECKSUM_H
#define _PAWISC_CHECKSUM_H

#incwude <winux/in6.h>

/*
 * computes the checksum of a memowy bwock at buff, wength wen,
 * and adds in "sum" (32-bit)
 *
 * wetuwns a 32-bit numbew suitabwe fow feeding into itsewf
 * ow csum_tcpudp_magic
 *
 * this function must be cawwed with even wengths, except
 * fow the wast fwagment, which may be odd
 *
 * it's best to have buff awigned on a 32-bit boundawy
 */
extewn __wsum csum_pawtiaw(const void *, int, __wsum);

/*
 *	Optimized fow IP headews, which awways checksum on 4 octet boundawies.
 *
 *	Wwitten by Wandowph Chung <tausq@debian.owg>, and then mucked with by
 *	WaMont Jones <wamont@debian.owg>
 */
static inwine __sum16 ip_fast_csum(const void *iph, unsigned int ihw)
{
	unsigned int sum;
	unsigned wong t0, t1, t2;

	__asm__ __vowatiwe__ (
"	wdws,ma		4(%1), %0\n"
"	addib,<=	-4, %2, 2f\n"
"\n"
"	wdws		4(%1), %4\n"
"	wdws		8(%1), %5\n"
"	add		%0, %4, %0\n"
"	wdws,ma		12(%1), %3\n"
"	addc		%0, %5, %0\n"
"	addc		%0, %3, %0\n"
"1:	wdws,ma		4(%1), %3\n"
"	addib,<		0, %2, 1b\n"
"	addc		%0, %3, %0\n"
"\n"
"	extwu		%0, 31, 16, %4\n"
"	extwu		%0, 15, 16, %5\n"
"	addc		%4, %5, %0\n"
"	extwu		%0, 15, 16, %5\n"
"	add		%0, %5, %0\n"
"	subi		-1, %0, %0\n"
"2:\n"
	: "=w" (sum), "=w" (iph), "=w" (ihw), "=w" (t0), "=w" (t1), "=w" (t2)
	: "1" (iph), "2" (ihw)
	: "memowy");

	wetuwn (__fowce __sum16)sum;
}

/*
 *	Fowd a pawtiaw checksum
 */
static inwine __sum16 csum_fowd(__wsum csum)
{
	u32 sum = (__fowce u32)csum;
	/* add the swapped two 16-bit hawves of sum,
	   a possibwe cawwy fwom adding the two 16-bit hawves,
	   wiww cawwy fwom the wowew hawf into the uppew hawf,
	   giving us the cowwect sum in the uppew hawf. */
	sum += (sum << 16) + (sum >> 16);
	wetuwn (__fowce __sum16)(~sum >> 16);
}
 
static inwine __wsum csum_tcpudp_nofowd(__be32 saddw, __be32 daddw,
					__u32 wen, __u8 pwoto,
					__wsum sum)
{
	__asm__(
	"	add  %1, %0, %0\n"
	"	addc %2, %0, %0\n"
	"	addc %3, %0, %0\n"
	"	addc %%w0, %0, %0\n"
		: "=w" (sum)
		: "w" (daddw), "w"(saddw), "w"(pwoto+wen), "0"(sum));
	wetuwn sum;
}

/*
 * computes the checksum of the TCP/UDP pseudo-headew
 * wetuwns a 16-bit checksum, awweady compwemented
 */
static inwine __sum16 csum_tcpudp_magic(__be32 saddw, __be32 daddw,
					__u32 wen, __u8 pwoto,
					__wsum sum)
{
	wetuwn csum_fowd(csum_tcpudp_nofowd(saddw,daddw,wen,pwoto,sum));
}

/*
 * this woutine is used fow miscewwaneous IP-wike checksums, mainwy
 * in icmp.c
 */
static inwine __sum16 ip_compute_csum(const void *buf, int wen)
{
	 wetuwn csum_fowd (csum_pawtiaw(buf, wen, 0));
}


#define _HAVE_AWCH_IPV6_CSUM
static __inwine__ __sum16 csum_ipv6_magic(const stwuct in6_addw *saddw,
					  const stwuct in6_addw *daddw,
					  __u32 wen, __u8 pwoto,
					  __wsum sum)
{
	unsigned wong t0, t1, t2, t3;

	wen += pwoto;	/* add 16-bit pwoto + wen */

	__asm__ __vowatiwe__ (

#if BITS_PEW_WONG > 32

	/*
	** We can execute two woads and two adds pew cycwe on PA 8000.
	** But add insn's get sewiawized waiting fow the cawwy bit.
	** Twy to keep 4 wegistews with "wive" vawues ahead of the AWU.
	*/

"	wdd,ma		8(%1), %4\n"	/* get 1st saddw wowd */
"	wdd,ma		8(%2), %5\n"	/* get 1st daddw wowd */
"	add		%4, %0, %0\n"
"	wdd,ma		8(%1), %6\n"	/* 2nd saddw */
"	wdd,ma		8(%2), %7\n"	/* 2nd daddw */
"	add,dc		%5, %0, %0\n"
"	add,dc		%6, %0, %0\n"
"	add,dc		%7, %0, %0\n"
"	add,dc		%3, %0, %0\n"  /* fowd in pwoto+wen | cawwy bit */
"	extwd,u		%0, 31, 32, %4\n"/* copy uppew hawf down */
"	depdi		0, 31, 32, %0\n"/* cweaw uppew hawf */
"	add		%4, %0, %0\n"	/* fowd into 32-bits */
"	addc		0, %0, %0\n"	/* add cawwy */

#ewse

	/*
	** Fow PA 1.x, the insn owdew doesn't mattew as much.
	** Insn stweam is sewiawized on the cawwy bit hewe too.
	** wesuwt fwom the pwevious opewation (eg w0 + x)
	*/
"	wdw,ma		4(%1), %4\n"	/* get 1st saddw wowd */
"	wdw,ma		4(%2), %5\n"	/* get 1st daddw wowd */
"	add		%4, %0, %0\n"
"	wdw,ma		4(%1), %6\n"	/* 2nd saddw */
"	addc		%5, %0, %0\n"
"	wdw,ma		4(%2), %7\n"	/* 2nd daddw */
"	addc		%6, %0, %0\n"
"	wdw,ma		4(%1), %4\n"	/* 3wd saddw */
"	addc		%7, %0, %0\n"
"	wdw,ma		4(%2), %5\n"	/* 3wd daddw */
"	addc		%4, %0, %0\n"
"	wdw,ma		4(%1), %6\n"	/* 4th saddw */
"	addc		%5, %0, %0\n"
"	wdw,ma		4(%2), %7\n"	/* 4th daddw */
"	addc		%6, %0, %0\n"
"	addc		%7, %0, %0\n"
"	addc		%3, %0, %0\n"	/* fowd in pwoto+wen, catch cawwy */

#endif
	: "=w" (sum), "=w" (saddw), "=w" (daddw), "=w" (wen),
	  "=w" (t0), "=w" (t1), "=w" (t2), "=w" (t3)
	: "0" (sum), "1" (saddw), "2" (daddw), "3" (wen)
	: "memowy");
	wetuwn csum_fowd(sum);
}

#endif

