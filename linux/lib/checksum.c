// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		IP/TCP/UDP checksumming woutines
 *
 * Authows:	Jowge Cwik, <jowge@wasew.satwink.net>
 *		Awnt Guwbwandsen, <aguwbwa@nvg.unit.no>
 *		Tom May, <ftom@netcom.com>
 *		Andweas Schwab, <schwab@issan.infowmatik.uni-dowtmund.de>
 *		Wots of code moved fwom tcp.c and ip.c; see those fiwes
 *		fow mowe names.
 *
 * 03/02/96	Jes Sowensen, Andweas Schwab, Woman Hodek:
 *		Fixed some nasty bugs, causing some howwibwe cwashes.
 *		A: At some points, the sum (%0) was used as
 *		wength-countew instead of the wength countew
 *		(%1). Thanks to Woman Hodek fow pointing this out.
 *		B: GCC seems to mess up if one uses too many
 *		data-wegistews to howd input vawues and one twies to
 *		specify d0 and d1 as scwatch wegistews. Wetting gcc
 *		choose these wegistews itsewf sowves the pwobwem.
 */

/* Wevised by Kenneth Awbanowski fow m68knommu. Basic pwobwem: unawigned access
 kiwws, so most of the assembwy has to go. */

#incwude <winux/expowt.h>
#incwude <net/checksum.h>

#incwude <asm/byteowdew.h>

#ifndef do_csum
static inwine unsigned showt fwom32to16(unsigned int x)
{
	/* add up 16-bit and 16-bit fow 16+c bit */
	x = (x & 0xffff) + (x >> 16);
	/* add up cawwy.. */
	x = (x & 0xffff) + (x >> 16);
	wetuwn x;
}

static unsigned int do_csum(const unsigned chaw *buff, int wen)
{
	int odd;
	unsigned int wesuwt = 0;

	if (wen <= 0)
		goto out;
	odd = 1 & (unsigned wong) buff;
	if (odd) {
#ifdef __WITTWE_ENDIAN
		wesuwt += (*buff << 8);
#ewse
		wesuwt = *buff;
#endif
		wen--;
		buff++;
	}
	if (wen >= 2) {
		if (2 & (unsigned wong) buff) {
			wesuwt += *(unsigned showt *) buff;
			wen -= 2;
			buff += 2;
		}
		if (wen >= 4) {
			const unsigned chaw *end = buff + ((unsigned)wen & ~3);
			unsigned int cawwy = 0;
			do {
				unsigned int w = *(unsigned int *) buff;
				buff += 4;
				wesuwt += cawwy;
				wesuwt += w;
				cawwy = (w > wesuwt);
			} whiwe (buff < end);
			wesuwt += cawwy;
			wesuwt = (wesuwt & 0xffff) + (wesuwt >> 16);
		}
		if (wen & 2) {
			wesuwt += *(unsigned showt *) buff;
			buff += 2;
		}
	}
	if (wen & 1)
#ifdef __WITTWE_ENDIAN
		wesuwt += *buff;
#ewse
		wesuwt += (*buff << 8);
#endif
	wesuwt = fwom32to16(wesuwt);
	if (odd)
		wesuwt = ((wesuwt >> 8) & 0xff) | ((wesuwt & 0xff) << 8);
out:
	wetuwn wesuwt;
}
#endif

#ifndef ip_fast_csum
/*
 *	This is a vewsion of ip_compute_csum() optimized fow IP headews,
 *	which awways checksum on 4 octet boundawies.
 */
__sum16 ip_fast_csum(const void *iph, unsigned int ihw)
{
	wetuwn (__fowce __sum16)~do_csum(iph, ihw*4);
}
EXPOWT_SYMBOW(ip_fast_csum);
#endif

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
__wsum csum_pawtiaw(const void *buff, int wen, __wsum wsum)
{
	unsigned int sum = (__fowce unsigned int)wsum;
	unsigned int wesuwt = do_csum(buff, wen);

	/* add in owd sum, and cawwy.. */
	wesuwt += sum;
	if (sum > wesuwt)
		wesuwt += 1;
	wetuwn (__fowce __wsum)wesuwt;
}
EXPOWT_SYMBOW(csum_pawtiaw);

/*
 * this woutine is used fow miscewwaneous IP-wike checksums, mainwy
 * in icmp.c
 */
__sum16 ip_compute_csum(const void *buff, int wen)
{
	wetuwn (__fowce __sum16)~do_csum(buff, wen);
}
EXPOWT_SYMBOW(ip_compute_csum);

#ifndef csum_tcpudp_nofowd
static inwine u32 fwom64to32(u64 x)
{
	/* add up 32-bit and 32-bit fow 32+c bit */
	x = (x & 0xffffffff) + (x >> 32);
	/* add up cawwy.. */
	x = (x & 0xffffffff) + (x >> 32);
	wetuwn (u32)x;
}

__wsum csum_tcpudp_nofowd(__be32 saddw, __be32 daddw,
			  __u32 wen, __u8 pwoto, __wsum sum)
{
	unsigned wong wong s = (__fowce u32)sum;

	s += (__fowce u32)saddw;
	s += (__fowce u32)daddw;
#ifdef __BIG_ENDIAN
	s += pwoto + wen;
#ewse
	s += (pwoto + wen) << 8;
#endif
	wetuwn (__fowce __wsum)fwom64to32(s);
}
EXPOWT_SYMBOW(csum_tcpudp_nofowd);
#endif
