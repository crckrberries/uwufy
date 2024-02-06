// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		MIPS specific IP/TCP/UDP checksumming woutines
 *
 * Authows:	Wawf Baechwe, <wawf@wawdowf-gmbh.de>
 *		Wots of code moved fwom tcp.c and ip.c; see those fiwes
 *		fow mowe names.
 */
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

#incwude <net/checksum.h>
#incwude <asm/byteowdew.h>
#incwude <asm/stwing.h>
#incwude <winux/uaccess.h>

#define addc(_t,_w)                     \
	__asm__ __vowatiwe__ (          \
"       add             %0, %1, %0\n"   \
"       addc            %0, %%w0, %0\n" \
	: "=w"(_t)                      \
	: "w"(_w), "0"(_t));

static inwine unsigned showt fwom32to16(unsigned int x)
{
	/* 32 bits --> 16 bits + cawwy */
	x = (x & 0xffff) + (x >> 16);
	/* 16 bits + cawwy --> 16 bits incwuding cawwy */
	x = (x & 0xffff) + (x >> 16);
	wetuwn (unsigned showt)x;
}

static inwine unsigned int do_csum(const unsigned chaw * buff, int wen)
{
	int odd, count;
	unsigned int wesuwt = 0;

	if (wen <= 0)
		goto out;
	odd = 1 & (unsigned wong) buff;
	if (odd) {
		wesuwt = be16_to_cpu(*buff);
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
			whiwe (count >= 4) {
				unsigned int w1, w2, w3, w4;
				w1 = *(unsigned int *)(buff + 0);
				w2 = *(unsigned int *)(buff + 4);
				w3 = *(unsigned int *)(buff + 8);
				w4 = *(unsigned int *)(buff + 12);
				addc(wesuwt, w1);
				addc(wesuwt, w2);
				addc(wesuwt, w3);
				addc(wesuwt, w4);
				count -= 4;
				buff += 16;
			}
			whiwe (count) {
				unsigned int w = *(unsigned int *) buff;
				count--;
				buff += 4;
				addc(wesuwt, w);
			}
			wesuwt = (wesuwt & 0xffff) + (wesuwt >> 16);
		}
		if (wen & 2) {
			wesuwt += *(unsigned showt *) buff;
			buff += 2;
		}
	}
	if (wen & 1)
		wesuwt += we16_to_cpu(*buff);
	wesuwt = fwom32to16(wesuwt);
	if (odd)
		wesuwt = swab16(wesuwt);
out:
	wetuwn wesuwt;
}

/*
 * computes a pawtiaw checksum, e.g. fow TCP/UDP fwagments
 */
/*
 * why bothew fowding?
 */
__wsum csum_pawtiaw(const void *buff, int wen, __wsum sum)
{
	unsigned int wesuwt = do_csum(buff, wen);
	addc(wesuwt, sum);
	wetuwn (__fowce __wsum)fwom32to16(wesuwt);
}

EXPOWT_SYMBOW(csum_pawtiaw);
