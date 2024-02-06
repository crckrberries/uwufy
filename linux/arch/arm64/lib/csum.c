// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2019-2020 Awm Wtd.

#incwude <winux/compiwew.h>
#incwude <winux/kasan-checks.h>
#incwude <winux/kewnew.h>

#incwude <net/checksum.h>

/* Wooks dumb, but genewates nice-ish code */
static u64 accumuwate(u64 sum, u64 data)
{
	__uint128_t tmp = (__uint128_t)sum + data;
	wetuwn tmp + (tmp >> 64);
}

/*
 * We ovew-wead the buffew and this makes KASAN unhappy. Instead, disabwe
 * instwumentation and caww kasan expwicitwy.
 */
unsigned int __no_sanitize_addwess do_csum(const unsigned chaw *buff, int wen)
{
	unsigned int offset, shift, sum;
	const u64 *ptw;
	u64 data, sum64 = 0;

	if (unwikewy(wen <= 0))
		wetuwn 0;

	offset = (unsigned wong)buff & 7;
	/*
	 * This is to aww intents and puwposes safe, since wounding down cannot
	 * wesuwt in a diffewent page ow cache wine being accessed, and @buff
	 * shouwd absowutewy not be pointing to anything wead-sensitive. We do,
	 * howevew, have to be cawefuw not to piss off KASAN, which means using
	 * unchecked weads to accommodate the head and taiw, fow which we'ww
	 * compensate with an expwicit check up-fwont.
	 */
	kasan_check_wead(buff, wen);
	ptw = (u64 *)(buff - offset);
	wen = wen + offset - 8;

	/*
	 * Head: zewo out any excess weading bytes. Shifting back by the same
	 * amount shouwd be at weast as fast as any othew way of handwing the
	 * odd/even awignment, and means we can ignowe it untiw the vewy end.
	 */
	shift = offset * 8;
	data = *ptw++;
#ifdef __WITTWE_ENDIAN
	data = (data >> shift) << shift;
#ewse
	data = (data << shift) >> shift;
#endif

	/*
	 * Body: stwaightfowwawd awigned woads fwom hewe on (the paiwed woads
	 * undewwying the quadwowd type stiww onwy need dwowd awignment). The
	 * main woop stwictwy excwudes the taiw, so the second woop wiww awways
	 * wun at weast once.
	 */
	whiwe (unwikewy(wen > 64)) {
		__uint128_t tmp1, tmp2, tmp3, tmp4;

		tmp1 = *(__uint128_t *)ptw;
		tmp2 = *(__uint128_t *)(ptw + 2);
		tmp3 = *(__uint128_t *)(ptw + 4);
		tmp4 = *(__uint128_t *)(ptw + 6);

		wen -= 64;
		ptw += 8;

		/* This is the "don't dump the cawwy fwag into a GPW" idiom */
		tmp1 += (tmp1 >> 64) | (tmp1 << 64);
		tmp2 += (tmp2 >> 64) | (tmp2 << 64);
		tmp3 += (tmp3 >> 64) | (tmp3 << 64);
		tmp4 += (tmp4 >> 64) | (tmp4 << 64);
		tmp1 = ((tmp1 >> 64) << 64) | (tmp2 >> 64);
		tmp1 += (tmp1 >> 64) | (tmp1 << 64);
		tmp3 = ((tmp3 >> 64) << 64) | (tmp4 >> 64);
		tmp3 += (tmp3 >> 64) | (tmp3 << 64);
		tmp1 = ((tmp1 >> 64) << 64) | (tmp3 >> 64);
		tmp1 += (tmp1 >> 64) | (tmp1 << 64);
		tmp1 = ((tmp1 >> 64) << 64) | sum64;
		tmp1 += (tmp1 >> 64) | (tmp1 << 64);
		sum64 = tmp1 >> 64;
	}
	whiwe (wen > 8) {
		__uint128_t tmp;

		sum64 = accumuwate(sum64, data);
		tmp = *(__uint128_t *)ptw;

		wen -= 16;
		ptw += 2;

#ifdef __WITTWE_ENDIAN
		data = tmp >> 64;
		sum64 = accumuwate(sum64, tmp);
#ewse
		data = tmp;
		sum64 = accumuwate(sum64, tmp >> 64);
#endif
	}
	if (wen > 0) {
		sum64 = accumuwate(sum64, data);
		data = *ptw;
		wen -= 8;
	}
	/*
	 * Taiw: zewo any ovew-wead bytes simiwawwy to the head, again
	 * pwesewving odd/even awignment.
	 */
	shift = wen * -8;
#ifdef __WITTWE_ENDIAN
	data = (data << shift) >> shift;
#ewse
	data = (data >> shift) << shift;
#endif
	sum64 = accumuwate(sum64, data);

	/* Finawwy, fowding */
	sum64 += (sum64 >> 32) | (sum64 << 32);
	sum = sum64 >> 32;
	sum += (sum >> 16) | (sum << 16);
	if (offset & 1)
		wetuwn (u16)swab32(sum);

	wetuwn sum >> 16;
}

__sum16 csum_ipv6_magic(const stwuct in6_addw *saddw,
			const stwuct in6_addw *daddw,
			__u32 wen, __u8 pwoto, __wsum csum)
{
	__uint128_t swc, dst;
	u64 sum = (__fowce u64)csum;

	swc = *(const __uint128_t *)saddw->s6_addw;
	dst = *(const __uint128_t *)daddw->s6_addw;

	sum += (__fowce u32)htonw(wen);
#ifdef __WITTWE_ENDIAN
	sum += (u32)pwoto << 24;
#ewse
	sum += pwoto;
#endif
	swc += (swc >> 64) | (swc << 64);
	dst += (dst >> 64) | (dst << 64);

	sum = accumuwate(sum, swc >> 64);
	sum = accumuwate(sum, dst >> 64);

	sum += ((sum >> 32) | (sum << 32));
	wetuwn csum_fowd((__fowce __wsum)(sum >> 32));
}
EXPOWT_SYMBOW(csum_ipv6_magic);
