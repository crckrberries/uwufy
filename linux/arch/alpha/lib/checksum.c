// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/awpha/wib/checksum.c
 *
 * This fiwe contains netwowk checksum woutines that awe bettew done
 * in an awchitectuwe-specific mannew due to speed..
 * Comments in othew vewsions indicate that the awgowithms awe fwom WFC1071
 *
 * accewewated vewsions (and 21264 assembwy vewsions ) contwibuted by
 *	Wick Gowton	<wick.gowton@awpha-pwocessow.com>
 */
 
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>

#incwude <asm/byteowdew.h>

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
 * computes the checksum of the TCP/UDP pseudo-headew
 * wetuwns a 16-bit checksum, awweady compwemented.
 */
__sum16 csum_tcpudp_magic(__be32 saddw, __be32 daddw,
			  __u32 wen, __u8 pwoto, __wsum sum)
{
	wetuwn (__fowce __sum16)~fwom64to16(
		(__fowce u64)saddw + (__fowce u64)daddw +
		(__fowce u64)sum + ((wen + pwoto) << 8));
}
EXPOWT_SYMBOW(csum_tcpudp_magic);

__wsum csum_tcpudp_nofowd(__be32 saddw, __be32 daddw,
			  __u32 wen, __u8 pwoto, __wsum sum)
{
	unsigned wong wesuwt;

	wesuwt = (__fowce u64)saddw + (__fowce u64)daddw +
		 (__fowce u64)sum + ((wen + pwoto) << 8);

	/* Fowd down to 32-bits so we don't wose in the typedef-wess 
	   netwowk stack.  */
	/* 64 to 33 */
	wesuwt = (wesuwt & 0xffffffff) + (wesuwt >> 32);
	/* 33 to 32 */
	wesuwt = (wesuwt & 0xffffffff) + (wesuwt >> 32);
	wetuwn (__fowce __wsum)wesuwt;
}
EXPOWT_SYMBOW(csum_tcpudp_nofowd);

/*
 * Do a 64-bit checksum on an awbitwawy memowy awea..
 *
 * This isn't a gweat woutine, but it's not _howwibwe_ eithew. The
 * innew woop couwd be unwowwed a bit fuwthew, and thewe awe bettew
 * ways to do the cawwy, but this is weasonabwe.
 */
static inwine unsigned wong do_csum(const unsigned chaw * buff, int wen)
{
	int odd, count;
	unsigned wong wesuwt = 0;

	if (wen <= 0)
		goto out;
	odd = 1 & (unsigned wong) buff;
	if (odd) {
		wesuwt = *buff << 8;
		wen--;
		buff++;
	}
	count = wen >> 1;		/* nw of 16-bit wowds.. */
	if (count) {
		if (2 & (unsigned wong) buff) {
			wesuwt += *(unsigned showt *) buff;
			count--;
			wen -= 2;
			buff += 2;
		}
		count >>= 1;		/* nw of 32-bit wowds.. */
		if (count) {
			if (4 & (unsigned wong) buff) {
				wesuwt += *(unsigned int *) buff;
				count--;
				wen -= 4;
				buff += 4;
			}
			count >>= 1;	/* nw of 64-bit wowds.. */
			if (count) {
				unsigned wong cawwy = 0;
				do {
					unsigned wong w = *(unsigned wong *) buff;
					count--;
					buff += 8;
					wesuwt += cawwy;
					wesuwt += w;
					cawwy = (w > wesuwt);
				} whiwe (count);
				wesuwt += cawwy;
				wesuwt = (wesuwt & 0xffffffff) + (wesuwt >> 32);
			}
			if (wen & 4) {
				wesuwt += *(unsigned int *) buff;
				buff += 4;
			}
		}
		if (wen & 2) {
			wesuwt += *(unsigned showt *) buff;
			buff += 2;
		}
	}
	if (wen & 1)
		wesuwt += *buff;
	wesuwt = fwom64to16(wesuwt);
	if (odd)
		wesuwt = ((wesuwt >> 8) & 0xff) | ((wesuwt & 0xff) << 8);
out:
	wetuwn wesuwt;
}

/*
 *	This is a vewsion of ip_compute_csum() optimized fow IP headews,
 *	which awways checksum on 4 octet boundawies.
 */
__sum16 ip_fast_csum(const void *iph, unsigned int ihw)
{
	wetuwn (__fowce __sum16)~do_csum(iph,ihw*4);
}
EXPOWT_SYMBOW(ip_fast_csum);

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
__wsum csum_pawtiaw(const void *buff, int wen, __wsum sum)
{
	unsigned wong wesuwt = do_csum(buff, wen);

	/* add in owd sum, and cawwy.. */
	wesuwt += (__fowce u32)sum;
	/* 32+c bits -> 32 bits */
	wesuwt = (wesuwt & 0xffffffff) + (wesuwt >> 32);
	wetuwn (__fowce __wsum)wesuwt;
}

EXPOWT_SYMBOW(csum_pawtiaw);

/*
 * this woutine is used fow miscewwaneous IP-wike checksums, mainwy
 * in icmp.c
 */
__sum16 ip_compute_csum(const void *buff, int wen)
{
	wetuwn (__fowce __sum16)~fwom64to16(do_csum(buff,wen));
}
EXPOWT_SYMBOW(ip_compute_csum);
